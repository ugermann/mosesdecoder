// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil -*-
#pragma once

#include <algorithm>

#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/math/distributions/binomial.hpp>

#include "ug_bitext.h"
#include "ug_bitext_pstats.h"
#include "ug_sampling_bias.h"
#include "ug_tsa_array_entry.h"
#include "ug_bitext_phrase_extraction_record.h"
#include "moses/TranslationModel/UG/generic/threading/ug_ref_counter.h"
#include "moses/TranslationModel/UG/generic/threading/ug_thread_safe_counter.h"
#include "moses/TranslationModel/UG/generic/sorting/NBestList.h"

#include "fisheryates.h"

namespace sapt
{

typedef std::vector<id_type> SrcPhrase;
typedef std::size_t size_t;  // make CLion happy

enum 
sampling_method 
  { 
    full_coverage, 
    random_sampling, 
    ranked_sampling, 
    ranked_sampling2,
    ranked_sampling3
  };
  
typedef ttrack::Position TokenPosition;
class CandidateSorter
{
  SamplingBias const& score;
public:
  CandidateSorter(SamplingBias const& s) : score(s) {}
  bool operator()(TokenPosition const& a, TokenPosition const& b) const
  { return score[a.sid] > score[b.sid]; }
};
  
template<typename Token>
class
BitextSampler : public Moses::reference_counter
{
  typedef Bitext<Token> bitext;
  typedef TSA<Token>       tsa;
  typedef SamplingBias    bias_t;
  typedef typename Bitext<Token>::iter tsa_iter;
  mutable boost::condition_variable   m_ready; 
  mutable boost::mutex                 m_lock; 
  // const members
  // SPTR<bitext const> const   m_bitext; // keep bitext alive while I am 
  // should be an 
  SPTR<bitext const> const       m_bitext; // keep bitext alive as long as I am 
  size_t             const         m_plen; // length of lookup phrase
  bool               const          m_fwd; // forward or backward direction?
  SPTR<tsa const>    const         m_root; // root of suffix array
  char               const*        m_next; // current position
  char               const*        m_stop; // end of search range
  sampling_method    const       m_method; // look at all/random/ranked samples 
  SPTR<bias_t const> const         m_bias; // bias over candidates
  size_t             const      m_samples; // how many samples at most 
  size_t             const  m_min_samples;
  // non-const members
  SPTR<pstats>                m_stats; // destination for phrase stats
  size_t                        m_ctr; // number of samples considered
  float                  m_total_bias; // for random sampling with bias
  bool                     m_finished;
  size_t m_num_occurrences; // estimated number of phrase occurrences in corpus
  boost::taus88 m_rnd;  // every job has its own pseudo random generator
  double m_bias_total;

  size_t m_random_size_t;
  double m_rnd_float;

  SrcPhrase m_phrase;

  /**
   * Attempt to extract a phrase pair, and on success, add it to m_stats.
   * @param p: the source phrase (as corpus location + implicit length in m_plen)
   * @ param i1: corpus index 1 to use (may be domain-specific)
   * @ param i2: index 2
   */
  size_t consider_sample(TokenPosition const& p, SPTR<TSA<Token> > i1, SPTR<TSA<Token> > i2);

  size_t consider_sample(TokenPosition const& p);

  size_t perform_random_sampling();
  size_t perform_full_phrase_extraction();

  int check_sample_distribution(uint64_t const& sid, uint64_t const& offset);
  bool flip_coin(tpt::id_type const& sid, tpt::offset_type const& offset,
                 SamplingBias const* bias);
  bool 
  flip_coin(size_t options_total, 
            size_t const options_considered, 
            size_t const options_chosen,
            size_t const threshold);
  
public:
  BitextSampler(BitextSampler const& other);
  // BitextSampler const& operator=(BitextSampler const& other);
  BitextSampler(SPTR<bitext const> const& bitext,
                SrcPhrase const& phrase,
                bool fwd,
                SPTR<SamplingBias const> const& bias, 
                size_t const min_samples, 
                size_t const max_samples,
                sampling_method const method); 
  ~BitextSampler();
  SPTR<pstats> stats();
  bool done() const;


// Ranked sampling sorts all samples by score and then considers the
// top-ranked candidates for phrase extraction.

//namespace bitext {
private:
  // ranked sampling on individual domain indexes
  size_t
  perform_ranked_sampling3()
  {
    // to do: static assert: bitext is convertible to mmBitext (Mmsapt only uses BitextSampler on mmBitext)
    const mmBitext<Token>& bitext = reinterpret_cast<const mmBitext<Token>&>(*m_bitext);
    // to do: static assert: convertible to document bias
    const DocumentBias& domBias = reinterpret_cast<const DocumentBias&>(*m_bias);

    assert(bitext.domainI1.size() > 0); // rudimentary check for presence of domain indexes

    std::vector<std::pair<float, id_type> > domScores;
    domBias.getRankedBias(domScores);

    size_t needSamples = m_samples; // remaining samples to be collected

    // in descending order of score, collect samples from each domain
    std::vector<std::pair<float, id_type> >::iterator it;
    for(it = domScores.begin(); needSamples > 0 && it != domScores.end(); it++) {
      id_type idom = it->second;
      needSamples -= ranked3_collect(needSamples, bitext.domainI1[idom], bitext.domainI2[idom]);
    }

    return 0; // nobody actually uses this.  AFAICT, this should be number of attempted samples.
  }

  /**
   * Try to collect samples from given domain, and return actual amount collected there.
   */
  size_t ranked3_collect(size_t samples, SPTR<TSA<Token> > i1, SPTR<TSA<Token> > i2) {
    size_t good_before = m_stats->good;
    //size_t good_target = good_before + samples; // should always be m_samples here.

    typename TSA<Token>::tree_iterator mfix(i1.get(), reinterpret_cast<const Token*>(m_phrase.data()), m_phrase.size());

    // check if we found anything at all (at least the first word) -- otherwise, rawCnt() fails.
    if(mfix.size() == 0)
      return 0;

    size_t occurrences = mfix.rawCnt();

    std::vector<size_t> sampleIndices;
    // generate sample indices
    random_indices(std::min(samples, occurrences), occurrences, m_rnd, sampleIndices);

    //while(m_stats->good < good_target) {
    std::vector<size_t>::iterator it;
    for(it = sampleIndices.begin(); it != sampleIndices.end(); it++) {
      // to do: nicer random access syntax?
      sapt::tsa::ArrayEntry I(i1.get(), mfix.index_jump_precise(*it));
      consider_sample(I, i1, i2);
    }

    return m_stats->good - good_before;
  }


// the original ranked sampling
  size_t
  perform_ranked_sampling()
  {
    if (m_next == m_stop) return m_ctr;

    CandidateSorter sorter(*m_bias);

    // below: nbest size = 2 * m_samples to allow for failed phrase extraction
    Moses::NBestList<TokenPosition, CandidateSorter> nbest(2*m_samples, sorter);
    sapt::tsa::ArrayEntry I(m_next);

    // collect candidates, keep track of how many rejected candidates
    // are tied with the lowest-scoring one.
    size_t tied = 0;
    while (I.next < m_stop)
    {
      ++m_ctr;
      m_root->readEntry(I.next, I);
      if (nbest.size() >= 2 * m_samples)
      {
        float s = (*m_bias)[I.sid];
        float th = (*m_bias)[nbest.get_unsorted(0).sid];
        if (s <= th)
        {
          if (s == th) ++tied;
          continue;
        }
        else tied = 0;
      }
      nbest.add(I);
    }

    // find upper end of threshold (not sure what 'upper end' means in heap of nbest)
    float th = (*m_bias)[nbest.get_unsorted(0).sid];
    size_t stop = nbest.size();
    while (stop && (*m_bias)[nbest[stop-1].sid] == th) --stop;
    tied += nbest.size() - stop;

    // From the highest-scoring candidate, go down the list and extract
    // phrases. If multiple phrase are tied and considering them all
    // would exceed the target sample size, select randomly

    // max_joint: highest number of joint phrase counts seen
    // good_enough: ninumum of max_joint required to stop sampling
    // Currently not used, so we set:
    size_t good_enough = m_samples;
    size_t max_joint = 0;
    size_t samples_considered = 0;
    for (size_t i=0,k; i < stop && max_joint < good_enough; i = k)
    {
      float s = (*m_bias)[nbest[i].sid];
      for (k = i+1; k < stop && (*m_bias)[nbest[k].sid] == s; ++k);
      if (m_stats->good + k - i <= m_samples)
      { // consider all occurrences
        for (; i < k; ++i)
          max_joint = std::max(max_joint, consider_sample(nbest[i]));
      }
      else
      {
        for (; i < k; ++i)
        {
          size_t random_number  = (k-i) * (m_rnd()/(m_rnd.max()+1.));
          if (m_stats->good + random_number < m_samples)
            max_joint = std::max(max_joint, consider_sample(nbest[i]));
        }
      }
    }

    // if we haven't met the quota yet, scan the occurrences again and
    // select randomly from the highest-scoring occurrences that haven't
    // been considered yet:

    if (tied == m_ctr)
      tied = m_stats->raw_cnt;

    if (m_stats->good < m_samples)
    {
      I.next = m_next;
      while (I.next < m_stop // && tied > 0 && max_joint < good_enough
             && m_stats->good < m_samples)
      {
        m_root->readEntry(I.next, I);
        if ((*m_bias)[I.sid] != th) continue;
        ++samples_considered;
        m_rnd_float  = (m_rnd()/(m_rnd.max()+1.));
        m_random_size_t = tied-- * m_rnd_float;

        if (m_stats->good + m_random_size_t < m_samples)
        {
          max_joint = std::max(max_joint, consider_sample(I));
        }
      }
    }
    return m_ctr;
  }


// Davide C.'s experimental variant of ranked sampling
  size_t
  perform_ranked_sampling2()
  {
    if (m_next == m_stop) return m_ctr;

    boost::shared_ptr<const sapt::DocumentBias> documentBias = boost::static_pointer_cast<const sapt::DocumentBias>(m_bias);
    const std::map<id_type, float> &biasMap = documentBias->GetDocumentBiasMap();

    id_type matchingDomainId = 0;
    float matchingDomainScore = -1.f;

    for(std::map<id_type, float>::const_iterator iterator = biasMap.begin(); iterator != biasMap.end(); ++iterator) {
      id_type id = iterator->first;
      float score = iterator->second;

      if (score > matchingDomainScore) {
        matchingDomainId = id;
        matchingDomainScore = score;
      }
    }

    size_t inDomainSamples = 0;

    sapt::tsa::ArrayEntry I(m_next);
    while (I.next < m_stop && m_stats->good < m_samples) {
      TokenPosition const& token = m_root->readEntry(I.next, I);
      id_type domain = m_bias->GetClass(token.sid);

      if (domain == matchingDomainId && consider_sample(token)) {
        inDomainSamples++;
      }

      ++m_ctr;
    }

    size_t min_samples = m_min_samples == 0 ? m_samples : m_min_samples;
    size_t outDomainSamples = 0;

    if (min_samples > 0 && inDomainSamples < min_samples) {
      CandidateSorter sorter(*m_bias);
      Moses::NBestList<TokenPosition, CandidateSorter> nbest(min_samples - inDomainSamples, sorter);
      I = sapt::tsa::ArrayEntry(m_next);

      while (I.next < m_stop) {
        TokenPosition const& token = m_root->readEntry(I.next, I);
        id_type domain = m_bias->GetClass(token.sid);

        if (domain != matchingDomainId && is_good_sample(token)) {
          nbest.add(token);
        }
      }

      for (size_t i = 0; i < nbest.size(); ++i) {
        if (consider_sample(nbest[i])) {
          outDomainSamples++;
        }
      }
    }

    if (m_bias->loglevel > 1) {
      *(m_bias->log) << "RANKED SAMPLING: found " << (outDomainSamples + inDomainSamples) << " samples. IN " << inDomainSamples << ", OUT " << outDomainSamples << std::endl;
    }

    return m_ctr;
  }


// auxiliary function for Davide C.'s variant of ranked sampling
  bool
  is_good_sample(TokenPosition const& p)
  {
    std::vector<unsigned char> aln;
    bitvector full_aln(100*100);
    PhraseExtractionRecord rec(p.sid, p.offset, p.offset + m_plen, !m_fwd, &aln, &full_aln);

    return m_bitext->find_trg_phr_bounds(rec);
  }


public:
  bool
  operator()()
  {
    if (m_finished) return true;
    boost::unique_lock<boost::mutex> lock(m_lock);
    if (m_method == full_coverage)
    {
      // std::cerr << "FULL COVERAGE " << HERE << std::endl;
      perform_full_phrase_extraction(); // consider all occurrences
    }
    else if (m_method == ranked_sampling)
    {
      // std::cerr << "RANKED SAMPLING " << HERE << std::endl;
      if (false and m_num_occurrences <= m_samples)
        perform_full_phrase_extraction();
      else if (m_bias)
        perform_ranked_sampling();
      else
      {
        // std::cerr
        // << "Ranked sampling requested but no bias given " << std::endl;
        perform_random_sampling();
      }
    }
    else if (m_method == ranked_sampling2)
      perform_ranked_sampling2();
    else if (m_method == ranked_sampling3)
      perform_ranked_sampling3();
    else if (m_method == random_sampling)
    {
      // std::cerr << "RANDOM SAMPLING " << HERE << std::endl;
      perform_random_sampling();
    }
    else UTIL_THROW2("Unsupported sampling method.");
    m_finished = true;
    m_ready.notify_all();
    return true;
  }
//}


};

template<typename Token>
int 
BitextSampler<Token>::
check_sample_distribution(uint64_t const& sid, uint64_t const& offset)
{ // ensure that the sampled distribution approximately matches the bias
  // @return 0: SKIP this occurrence
  // @return 1: consider this occurrence for sampling
  // @return 2: include this occurrence in the sample by all means

  typedef boost::math::binomial_distribution<> binomial;

  // std::ostream* log = m_bias->loglevel > 1 ? m_bias->log : NULL;
  std::ostream* log = NULL;

  if (!m_bias) return 1;

  float p = (*m_bias)[sid];
  id_type docid = m_bias->GetClass(sid);
 
  pstats::indoc_map_t::const_iterator m = m_stats->indoc.find(docid);
  uint32_t k = m != m_stats->indoc.end() ? m->second : 0 ;

  // always consider candidates from dominating documents and
  // from documents that have not been considered at all yet
  bool ret =  (p > .5 || k == 0);

  if (ret && !log) return 1;

  uint32_t N = m_stats->good; // number of trials
  float d = cdf(complement(binomial(N, p), k));
  // d: probability that samples contains k or more instances from doc #docid
  ret = ret || d >= .05;

#if 0
  if (log)
    {
      Token const* t = m_root->getCorpus()->sntStart(sid)+offset;
      Token const* x = t - std::min(offset,uint64_t(3));
      Token const* e = t + 4;
      if (e > m_root->getCorpus()->sntEnd(sid))
        e = m_root->getCorpus()->sntEnd(sid);
      *log << docid << ":" << sid << " " << size_t(k) << "/" << N
           << " @" << p << " => " << d << " [";
      pstats::indoc_map_t::const_iterator m;
      for (m = m_stats->indoc.begin(); m != m_stats->indoc.end(); ++m)
        {
          if (m != m_stats->indoc.begin()) *log << " ";
          *log << m->first << ":" << m->second;
        }
      *log << "] ";
      for (; x < e; ++x) *log << (*m_bitext->V1)[x->id()] << " ";
      if (!ret) *log << "SKIP";
      else if (p < .5 && d > .9) *log << "FORCE";
      *log << std::endl;
    }
#endif
  return (ret ? (p < .5 && d > .9) ? 2 : 1 : 0);
}

template<typename Token>
bool 
BitextSampler<Token>::
flip_coin(size_t options_total, 
          size_t const options_considered, 
          size_t const options_chosen,
          size_t const threshold) 
{
  if (options_considered > options_total)
    options_total = options_considered;
  size_t options_left = (options_total - options_considered);
  m_rnd_float = (m_rnd()/(m_rnd.max()+1.));
  m_random_size_t = options_left * m_rnd_float;
  return m_random_size_t + options_chosen < threshold;
}

template<typename Token>
bool 
BitextSampler<Token>::
flip_coin(tpt::id_type const& sid, tpt::offset_type const& offset, bias_t const* bias)
{
  int no_maybe_yes = bias ? check_sample_distribution(sid, offset) : 1;
  if (no_maybe_yes == 0) return false; // no
  if (no_maybe_yes > 1)  return true;  // yes
  // ... maybe: flip a coin
  size_t options_total  = std::max(m_stats->raw_cnt, m_ctr);
  size_t threshold = ((bias && m_bias_total > 0 && m_method != ranked_sampling)
                      ? round((*bias)[sid]/m_bias_total * options_total * m_samples) // w/ bias
                      : m_samples); // no bias
  return flip_coin(m_stats->raw_cnt, m_ctr, m_stats->good,threshold);
}

template<typename Token>
BitextSampler<Token>::
BitextSampler(SPTR<Bitext<Token> const> const& bitext,
              SrcPhrase const& phrase,
              bool fwd,
              SPTR<SamplingBias const> const& bias, 
              size_t const min_samples, 
              size_t const max_samples,
              sampling_method const method)
  : m_bitext(bitext)
  , m_plen(phrase.size())
  , m_fwd(fwd)
  , m_root(m_fwd ? bitext->I1 : bitext->I2)
  , m_method(method)
  , m_bias(bias)
  , m_samples(max_samples)
  , m_min_samples(min_samples)
  , m_ctr(0)
  , m_total_bias(0)
  , m_finished(false)
  , m_rnd(0)
  , m_phrase(phrase)
{
  m_stats.reset(new pstats);
  m_stats->raw_cnt = phrase.ca();
  m_stats->register_worker();

  typename TSA<Token>::tree_iterator mfix(m_bitext->I1.get(),reinterpret_cast<const Token*>(phrase.data()),phrase.size());

  m_next = mfix.lower_bound(-1);
  m_stop = mfix.upper_bound(-1);
  m_num_occurrences = (size_t) mfix.ca();

  m_stats->raw_cnt = mfix.rawCnt(); // .ca();
}
  
template<typename Token>
BitextSampler<Token>::
BitextSampler(BitextSampler const& other)
  : m_bitext(other.m_bitext)
  , m_plen(other.m_plen)
  , m_fwd(other.m_fwd)
  , m_root(other.m_root)
  , m_next(other.m_next)
  , m_stop(other.m_stop)
  , m_method(other.m_method)
  , m_bias(other.m_bias)
  , m_samples(other.m_samples)
  , m_min_samples(other.m_min_samples)
  , m_num_occurrences(other.m_num_occurrences)
  , m_rnd(0)
  , m_phrase(other.m_phrase)
{
  // lock both instances
  boost::unique_lock<boost::mutex> mylock(m_lock);
  boost::unique_lock<boost::mutex> yrlock(other.m_lock);
  // actually, BitextSamplers should only copied on job submission
  m_stats = other.m_stats;
  m_stats->register_worker();
  m_ctr = other.m_ctr; 
  m_total_bias = other.m_total_bias;
  m_finished = other.m_finished;
}


// Uniform sampling 
template<typename Token>
size_t
BitextSampler<Token>::
perform_full_phrase_extraction()
{
  if (m_next == m_stop) return m_ctr;
  for (sapt::tsa::ArrayEntry I(m_next); I.next < m_stop; ++m_ctr)
    {
      ++m_ctr;
      m_root->readEntry(I.next, I);
      consider_sample(I);
    }
  return m_ctr;
}


// Uniform sampling 
template<typename Token>
size_t
BitextSampler<Token>::
perform_random_sampling()
{
  if (m_next == m_stop) return m_ctr;
  m_bias_total = 0;
  sapt::tsa::ArrayEntry I(m_next);
  if (m_bias)
    {
      // Ranked and random sampling use approximate raw count
      // For consistency of results, biased sampling should also use the
      // approximate count
      // m_stats->raw_cnt = 0;
      while (I.next < m_stop)
        {
          m_root->readEntry(I.next,I);
          m_bias_total += (*m_bias)[I.sid];
        }
      I.next = m_next;
    }
      
  while (m_stats->good < m_samples && I.next < m_stop)
    {
      m_root->readEntry(I.next,I);
      bool foo = flip_coin(I.sid, I.offset, m_bias.get());
#if 0
      size_t options_total  = std::max(m_stats->raw_cnt, m_ctr);
      size_t threshold = ((m_bias && m_bias_total > 0 && m_method != ranked_sampling)
                          ? round((*m_bias)[I.sid]/m_bias_total * options_total * m_samples) // w/ bias
                          : m_samples); // no bias

      std::cerr << "[" << m_ctr << "/ " << m_stats->raw_cnt << ": " << m_rnd_float << "] " 
                << m_stats->good << " + " << m_random_size_t << " = " 
                << m_stats->good + m_random_size_t << " | " << threshold << "; "
                << I.sid << ":" << I.offset << " " << (foo ? "Y" : "N") << std::endl;
#endif
      ++m_ctr;
      size_t maxevid = foo ? consider_sample(I) : 0;
    }
  return m_ctr;
}

template<typename Token>
size_t
BitextSampler<Token>::
consider_sample(TokenPosition const& p)
{
  // by default, use the global index
  return consider_sample(p, m_bitext->I1, m_bitext->I2);
}

template<typename Token>
size_t
BitextSampler<Token>::
consider_sample(TokenPosition const& p, SPTR<TSA<Token> > i1, SPTR<TSA<Token> > i2)
{
  std::vector<unsigned char> aln; 
  bitvector full_aln(100*100);
  PhraseExtractionRecord 
    rec(p.sid, p.offset, p.offset + m_plen, !m_fwd, &aln, &full_aln);
  int docid = m_bias ? m_bias->GetClass(p.sid) : m_bitext->sid2did(p.sid);
  if (!m_bitext->find_trg_phr_bounds(rec))
    { // no good, probably because phrase is not coherent
      m_stats->count_sample(docid, 0, rec.po_fwd, rec.po_bwd);
      return 0;
    }
    
  // all good: register this sample as valid
  size_t num_pairs = (rec.s2 - rec.s1 + 1) * (rec.e2 - rec.e1 + 1);
  m_stats->count_sample(docid, num_pairs, rec.po_fwd, rec.po_bwd);
    
  float sample_weight = 1./num_pairs;
  Token const* o = (m_fwd ? m_bitext->T2 : m_bitext->T1)->sntStart(rec.sid);
    
  // adjust offsets in phrase-internal aligment
  for (size_t k = 1; k < aln.size(); k += 2) 
    aln[k] += rec.s2 - rec.s1;
    
  std::vector<uint64_t> seen; seen.reserve(10);
  // It is possible that the phrase extraction extracts the same
  // phrase twice, e.g., when word a co-occurs with sequence b b b but
  // is aligned only to the middle word. We can only count each phrase
  // pair once per source phrase occurrence, or else run the risk of
  // having more joint counts than marginal counts.
    
  size_t max_evidence = 0;
  for (size_t s = rec.s1; s <= rec.s2; ++s)
    {
      TSA<Token> const& I = m_fwd ? *i2 : *i1;
      SPTR<tsa_iter> b = I.find(o + s, rec.e1 - s);
      UTIL_THROW_IF2(!b || b->size() < rec.e1 - s, "target phrase not found");

      phrase<Token> trg(o + s, rec.e1 - s);

      for (size_t i = rec.e1; i <= rec.e2; ++i)
        {
          uint64_t tpid = b->getPid();
          if (find(seen.begin(), seen.end(), tpid) != seen.end()) 
            continue; // don't over-count
          seen.push_back(tpid);
          size_t raw2 = b->approxOccurrenceCount();
          size_t evid = m_stats->add(tpid, (phrase<id_type> &) trg, sample_weight,
                                     m_bias ? (*m_bias)[p.sid] : 1, 
                                     aln, raw2, rec.po_fwd, rec.po_bwd, docid);
          max_evidence = std::max(max_evidence, evid);
          bool ok = (i == rec.e2) || b->extend(o[i].id());
          UTIL_THROW_IF2(!ok, "Could not extend target phrase.");
        }
      if (s < rec.s2) // shift phrase-internal alignments
        for (size_t k = 1; k < aln.size(); k += 2)
          --aln[k];
    }
  return max_evidence;
}

template<typename Token>
bool
BitextSampler<Token>::
done() const 
{
  return m_next == m_stop;
}

template<typename Token>
SPTR<pstats> 
BitextSampler<Token>::
stats() 
{
  // if (m_ctr == 0) (*this)();
  // boost::unique_lock<boost::mutex> lock(m_lock);
  // while (!m_finished)
  // m_ready.wait(lock);
  return m_stats;
}

template<typename Token>
BitextSampler<Token>::
~BitextSampler()
{ 
  m_stats->release();
}

} // end of namespace sapt

