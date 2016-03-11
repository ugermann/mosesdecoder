// $Id$

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#include <limits>
#include <iostream>
#include <fstream>
#include "dictionary.h"
#include "n_gram.h"
#include "lmContainer.h"

using namespace irstlm;

#include "IRST.h"
#include "SingleFactor.h"
#include "moses/FF/FFState.h"
#include "moses/TypeDef.h"
#include "moses/Util.h"
#include "moses/FactorCollection.h"
#include "moses/Phrase.h"
#include "moses/InputFileStream.h"
#include "moses/StaticData.h"
#include "moses/TranslationTask.h"

using namespace std;

namespace Moses
{
typedef unsigned int  ngram_state_t; //type for pointing to a full ngram in the table; must be equal to that define in IRSTLM toolkit

class IRSTLMState : public FFState
{
  // Allow LanguageModelIRST to access the private members of this class
  friend class LanguageModelIRST;
  friend ostream& operator<<(ostream& out, const IRSTLMState& obj);

 public:
  size_t hash() const
  {
    boost::hash<size_t> hasher;
    return hasher(state);
  }

  bool operator==(const FFState& o) const
  {
    const IRSTLMState &other = static_cast<const IRSTLMState &>(o);
    return (state == other.state);
  }

  IRSTLMState():state(0) {}

  IRSTLMState(ngram_state_t st):state(st) {}  

 private:
  ngram_state_t state;
};

// friend
ostream& operator<<(ostream& out, const IRSTLMState& obj)
{
  out << " obj.state:|" << obj.state << "|";
  return out;
}


/*
 * class IRSTLMState : public PointerState
{
public:
  IRSTLMState():PointerState(NULL)  {}
  IRSTLMState(const void* lms):PointerState(lms)  {}
  IRSTLMState(const IRSTLMState& copy_from):PointerState(copy_from.lmstate)  {}

  IRSTLMState& operator=( const IRSTLMState& rhs ) {
    lmstate = rhs.lmstate;
    return *this;
  }

  const void* GetState() const {
    return lmstate;
  }
};
*/

LanguageModelIRST::LanguageModelIRST(const std::string &line)
  :LanguageModelSingleFactor(line)
  ,m_lmtb_dub(IRSTLM_DUB_DEFAULT), m_lmtb_size(0)
{
//  ,m_lmtb_dub(0), m_lmtb_size(0)
/*
  const StaticData &staticData = StaticData::Instance();
  int threadCount = staticData.ThreadCount();
  if (threadCount != 1) {
    throw runtime_error("Error: " + SPrint(threadCount) + " number of threads specified but IRST LM is not threadsafe.");
  }
*/

      m_id = "default";
      m_weight_map_normalization = false;
      m_weight_map_limit = 0; //default is 0, i.e. no limits, take all available weights
      m_use_context_weights = false;
      ReadParameters();

      VERBOSE(3, GetScoreProducerDescription()
                 << " LanguageModelIRST::LanguageModelIRST() m_lmtb_dub:|"
                 << m_lmtb_dub << "|" << std::endl);
      VERBOSE(3, GetScoreProducerDescription()
                 << " LanguageModelIRST::LanguageModelIRST() m_filePath:|"
                 << m_filePath << "|" << std::endl);
      VERBOSE(3, GetScoreProducerDescription()
                 << " LanguageModelIRST::LanguageModelIRST() m_factorType:|"
                 << m_factorType << "|" << std::endl);
      VERBOSE(3, GetScoreProducerDescription()
                 << " LanguageModelIRST::LanguageModelIRST() m_id:|"
                 << m_id << "|" << std::endl);
      VERBOSE(3, GetScoreProducerDescription()
                 << " LanguageModelIRST::LanguageModelIRST() m_weight_map_normalization:|"
                 << m_weight_map_normalization << "|" << std::endl);
      VERBOSE(3, GetScoreProducerDescription()
                 << " LanguageModelIRST::LanguageModelIRST() m_weight_map_limit:|"
                 << m_weight_map_limit << "|" << std::endl);
      VERBOSE(3, GetScoreProducerDescription()
                 << " LanguageModelIRST::LanguageModelIRST() "
                 << "m_use_context_weights:|" << m_use_context_weights << "|"
                 << std::endl);
}

LanguageModelIRST::~LanguageModelIRST()
{

#ifndef WIN32
  VERBOSE(1,"reset mmap" << std::endl);
  if (m_lmtb) m_lmtb->reset_mmap();
#endif

  delete m_lmtb;
}


bool LanguageModelIRST::IsUseable(const FactorMask &mask) const
{
  bool ret = mask[m_factorType];
  return ret;
}

void LanguageModelIRST::Load(AllOptions::ptr const& opts)
{
  FactorCollection &factorCollection = FactorCollection::Instance();

  m_lmtb = m_lmtb->CreateLanguageModel(m_filePath);
  VERBOSE(3, GetScoreProducerDescription() << " LanguageModelIRST::Load() type:|" << m_lmtb->getLanguageModelType() << "|" << std::endl);

  if (m_lmtb_size > 0) m_lmtb->setMaxLoadedLevel(m_lmtb_size);
  VERBOSE(3, GetScoreProducerDescription() << " LanguageModelIRST::Load() m_lmtb_size:|" << m_lmtb_size << "|" << std::endl);

  m_lmtb->load(m_filePath);
  d=m_lmtb->getDict();
  d->incflag(1);

  m_nGramOrder = m_lmtb_size = m_lmtb->maxlevel();
  VERBOSE(3, GetScoreProducerDescription() << " LanguageModelIRST::Load() m_lmtb_size:|" << m_lmtb_size << "|" << std::endl);

  // LM can be ok, just outputs warnings
  // Mauro: in the original, the following two instructions are wrongly switched:
  m_unknownId = d->oovcode(); // at the level of micro tags
  m_empty = -1; // code for an empty position

  CreateFactors(factorCollection);

  VERBOSE(3, GetScoreProducerDescription() << " LanguageModelIRST::Load() m_unknownId=|" << m_unknownId << "|" << std::endl);

  //install caches to save time (only if PS_CACHE_ENABLE is defined through compilation flags)
  m_lmtb->init_caches(m_lmtb_size>2?m_lmtb_size-1:2);

  VERBOSE(3, GetScoreProducerDescription() << " LanguageModelIRST::Load() m_lmtb_dub:|" << m_lmtb_dub << "|" << std::endl);
  if (m_lmtb_dub > 0) m_lmtb->setlogOOVpenalty(m_lmtb_dub);
  VERBOSE(3, GetScoreProducerDescription() << " LanguageModelIRST::Load() oovpenalty:|" << m_lmtb->getlogOOVpenalty() << "|" << std::endl);
  d->incflag(0);
}

void LanguageModelIRST::CreateFactors(FactorCollection &factorCollection)
{
VERBOSE(1,"void LanguageModelIRST::CreateFactors(FactorCollection &factorCollection) START" << std::endl);
  // add factors which have srilm id
  // code copied & paste from SRI LM class. should do template function
  std::map<size_t, int> lmIdMap;
  size_t maxFactorId = 0; // to create lookup vector later on
  m_empty = -1; // code for an empty position

  dict_entry *entry;
  dictionary_iter iter(d); // at the level of micro tags
  while ( (entry = iter.next()) != NULL) {
    size_t factorId = factorCollection.AddFactor(Output, m_factorType, entry->word)->GetId();
    lmIdMap[factorId] = entry->code;
    maxFactorId = (factorId > maxFactorId) ? factorId : maxFactorId;
  }

  size_t factorId;

  m_sentenceStart = factorCollection.AddFactor(Output, m_factorType, BOS_);
  factorId = m_sentenceStart->GetId();
  d->incflag(1);
  m_lmtb_sentenceStart = lmIdMap[factorId] = GetLmID(BOS_);
  d->incflag(0);
  maxFactorId = (factorId > maxFactorId) ? factorId : maxFactorId;
  m_sentenceStartWord[m_factorType] = m_sentenceStart;

  m_sentenceEnd         = factorCollection.AddFactor(Output, m_factorType, EOS_);
  factorId = m_sentenceEnd->GetId();
  d->incflag(1);
  m_lmtb_sentenceEnd = lmIdMap[factorId] = GetLmID(EOS_);
  d->incflag(0);
  maxFactorId = (factorId > maxFactorId) ? factorId : maxFactorId;
  m_sentenceEndWord[m_factorType] = m_sentenceEnd;

  // add to lookup vector in object
  m_lmIdLookup.resize(maxFactorId+1);
  fill(m_lmIdLookup.begin(), m_lmIdLookup.end(), m_empty);

  map<size_t, int>::iterator iterMap;
  for (iterMap = lmIdMap.begin() ; iterMap != lmIdMap.end() ; ++iterMap) {
    m_lmIdLookup[iterMap->first] = iterMap->second;
  }
VERBOSE(1,"void LanguageModelIRST::CreateFactors(FactorCollection &factorCollection) END" << std::endl);
}

int LanguageModelIRST::GetLmID( const std::string &str ) const
{
  return d->encode( str.c_str() ); // at the level of micro tags
}

int LanguageModelIRST::GetLmID( const Word &word ) const
{
  return GetLmID( word.GetFactor(m_factorType) );
}

int LanguageModelIRST::GetLmID( const Factor *factor ) const
{
  size_t factorId = factor->GetId();
  if  ((factorId >= m_lmIdLookup.size()) || (m_lmIdLookup[factorId] == m_empty)) {
    return m_unknownId;
  }else {
    return m_lmIdLookup[factorId];
  }
}

/*
int LanguageModelIRST::GetLmID( const Factor *factor ) const
{
VERBOSE(1,"int LanguageModelIRST::GetLmID( const Factor *factor ) const version A" << std::endl;);
  size_t factorId = factor->GetId();
int c;
  if  ((factorId >= m_lmIdLookup.size()) || (m_lmIdLookup[factorId] == m_empty)) {
    if (d->incflag()==1) {
      std::string s = factor->GetString().as_string();
      int code = d->encode(s.c_str());

      //////////
      ///poiche' non c'e' distinzione tra i factorIDs delle parole sorgenti
      ///e delle parole target in Moses, puo' accadere che una parola target
      ///di cui non sia stato ancora calcolato il suo codice target abbia
      ///comunque un factorID noto (e quindi minore di m_lmIdLookup.size())
      ///E' necessario dunque identificare questi casi di indeterminatezza
      ///del codice target. Attualmente, questo controllo e' stato implementato
      ///impostando a    m_empty     tutti i termini che non hanno ancora
      //ricevuto un codice target effettivo
      ///////////

      ///OLD PROBLEM - SOLVED
////////////
/// IL PPROBLEMA ERA QUI
/// m_lmIdLookup.push_back(code);
/// PERCHE' USANDO PUSH_BACK IN REALTA' INSEREVIVAMO L'ELEMENTO NUOVO
/// IN POSIZIONE (factorID-1) invece che in posizione factrID dove dopo andiamo a leggerlo (vedi caso C
/// Cosi' funziona ....
/// ho un dubbio su cosa c'e' nelle prime posizioni di m_lmIdLookup
/// quindi
/// e scopro che rimane vuota una entry ogni due
/// perche' factorID cresce di due in due (perche' codifica sia source che target) "vuota" la posizione (factorID-1)
/// non da problemi di correttezza, ma solo di "spreco" di memoria
/// potremmo sostituirerendere  m_lmIdLookup una std:map invece che un std::vector,
/// ma si perde in efficienza nell'accesso perche' non e' piu' possibile quello random dei vettori
/// a te la scelta!!!!
////////////////


      if (factorId >= m_lmIdLookup.size()) {
        //resize and fill with m_empty
        //increment the array more than needed to avoid too many resizing operation.
        m_lmIdLookup.resize(factorId+10, m_empty);
      }

      //insert new code
      m_lmIdLookup[factorId] = code;
      c=code;
//      return code;

    } else {
      c=m_unknownId;
//      return m_unknownId;
    }
  } else {
    c=m_lmIdLookup[factorId];
//    return m_lmIdLookup[factorId];
  }
VERBOSE(1,"int LanguageModelIRST::GetLmID( const Factor *factor ) const version A: word:|" << s << "| code:|" << c << "|" << std::endl;);
  return c;
}
*/

const FFState* LanguageModelIRST::EmptyHypothesisState(const InputType &/*input*/) const
{
  VERBOSE(2,"const FFState* LanguageModelIRST::EmptyHypothesisState(const InputType &/*input*/)"<< std::endl);
  std::auto_ptr<IRSTLMState> ret(new IRSTLMState());

  return ret.release();
}


void LanguageModelIRST::CalcScore(const Phrase &phrase, float &fullScore, float &ngramScore, size_t &oovCount) const
{
  VERBOSE(2,"void LanguageModelIRST::CalcScore(const Phrase &phrase, ...) START id:|" << m_id << "| phrase:|" << phrase << "|" << std::endl);

  fullScore = 0;
  ngramScore = 0;
  oovCount = 0;

  if ( !phrase.GetSize() ) return;


  weightmap_t* weight_map = t_interpolation_weights.get();
//  weightmap_t* weight_map = t_interpolation_weights->get();

  int _min = min((int) m_lmtb_size - 1, (int) phrase.GetSize());

  int codes[m_lmtb_size];
  int idx = 0;
  codes[idx] = m_lmtb_sentenceStart;
  ++idx;
  int position = 0;

  float before_boundary = 0.0;
  for (; position < _min; ++position) {
    codes[idx] = GetLmID(phrase.GetWord(position));
    if (codes[idx] == m_unknownId) ++oovCount;

    if (weight_map && weight_map->size()>0)
      before_boundary += m_lmtb->clprob(codes,idx+1,*weight_map);
    else
      before_boundary += m_lmtb->clprob(codes,idx+1); 

    ++idx;
  }

  ngramScore = 0.0;
  int end_loop = (int) phrase.GetSize();

  for (; position < end_loop; ++position) {
    for (idx = 1; idx < m_lmtb_size; ++idx) {
      codes[idx-1] = codes[idx];
    }
    codes[idx-1] = GetLmID(phrase.GetWord(position));
    if (codes[idx-1] == m_unknownId) ++oovCount;

    if (weight_map && weight_map->size()>0)
      ngramScore += m_lmtb->clprob(codes,idx,*weight_map);
    else
      ngramScore += m_lmtb->clprob(codes,idx);
  }

  before_boundary = TransformLMScore(before_boundary);
  ngramScore = TransformLMScore(ngramScore);
  fullScore = ngramScore + before_boundary;
}


FFState* LanguageModelIRST::EvaluateWhenApplied(const Hypothesis &hypo, const FFState *ps, ScoreComponentCollection *out) const
{
  if (!hypo.GetCurrTargetLength()) {
    std::auto_ptr<IRSTLMState> ret(new IRSTLMState(*((IRSTLMState*)ps)));
    return ret.release();
  }

  //[begin, end) in STL-like fashion.
  const int begin = (const int) hypo.GetCurrTargetWordsRange().GetStartPos();
  const int end = (const int) hypo.GetCurrTargetWordsRange().GetEndPos() + 1;
  const int adjust_end = (const int) std::min(end, begin + (int) m_lmtb_size - 1);

  //set up context
  //fill the farthest positions with sentenceStart symbols, if "empty" positions are available
  //so that the vector looks like = "<s> <s> context_word context_word" for a two-word context and a LM of order 5
  int codes[m_lmtb_size];
  int idx=m_lmtb_size-1;
  int position = (const int) begin;
  while (position >= 0) {
    codes[idx] =  GetLmID(hypo.GetWord(position));
    --idx;
    --position;
  }
  while (idx>=0) {
    codes[idx] = m_lmtb_sentenceStart;
    --idx;
  }

  char* msp = NULL;
  ngram_state_t msidx = 0;
  float score;
  weightmap_t* weight_map = t_interpolation_weights.get();
//  weightmap_t* weight_map = t_interpolation_weights->get();
  if (weight_map && weight_map->size()>0){
    score = m_lmtb->clprob(codes,m_lmtb_size,*weight_map,NULL,NULL,&msidx,&msp);
  }else{
    score = m_lmtb->clprob(codes,m_lmtb_size,NULL,NULL,&msidx,&msp);
  }

  position = (const int) begin+1;
  while (position < adjust_end) {
    for (idx=1; idx<m_lmtb_size; idx++) {
      codes[idx-1] = codes[idx];
    }
    codes[idx-1] =  GetLmID(hypo.GetWord(position));
    if (weight_map && weight_map->size()>0){
      score += m_lmtb->clprob(codes,m_lmtb_size,*weight_map,NULL,NULL,&msidx,&msp);
    }else{
      score += m_lmtb->clprob(codes,m_lmtb_size,NULL,NULL,&msidx,&msp);
    }
    ++position;
  }

  //adding probability of having sentenceEnd symbol, after this phrase;
  //this could happen only when all source words are covered
  if (hypo.IsSourceCompleted()) {
    idx=m_lmtb_size-1;
    codes[idx] = m_lmtb_sentenceEnd;
    --idx;
    position = (const int) end - 1;
    while (position >= 0 && idx >= 0) {
      codes[idx] =  GetLmID(hypo.GetWord(position));
      --idx;
      --position;
    }
    while (idx>=0) {
      codes[idx] = m_lmtb_sentenceStart;
      --idx;
    }
    if (weight_map && weight_map->size()>0){
      score += m_lmtb->clprob(codes,m_lmtb_size,*weight_map,NULL,NULL,&msidx,&msp);
    }else{
      score += m_lmtb->clprob(codes,m_lmtb_size,NULL,NULL,&msidx,&msp);
    }
  } else {
    // need to set the LM state

    if (adjust_end < end)   { //the LMstate of this target phrase refers to the last m_lmtb_size-1 words
      position = (const int) end - 1;
      for (idx=m_lmtb_size-1; idx>0; --idx) {
        codes[idx] =  GetLmID(hypo.GetWord(position));
      }
      codes[idx] = m_lmtb_sentenceStart;
      msidx = m_lmtb->cmaxsuffidx(codes,m_lmtb_size);
    }
  }

  score = TransformLMScore(score);
  out->PlusEquals(this, score);

  std::auto_ptr<IRSTLMState> ret(new IRSTLMState(msidx));

  return ret.release();
}

LMResult LanguageModelIRST::GetValue(const vector<const Word*> &contextFactor, State* finalState) const
{ //dummy version
  VERBOSE(2,"LMResult LanguageModelIRST::GetValue(const vector<const Word*> &contextFactor, State* finalState)"<< std::endl);
  if (finalState) *finalState=NULL;
  LMResult result;
  result.unknown = 0.0;
  result.score = 0.0;
  
  return result;
}

bool LMCacheCleanup(const int sentences_done, const size_t m_lmcache_cleanup_threshold)
{
  if (sentences_done==-1) return true;
  if (m_lmcache_cleanup_threshold)
    if (sentences_done % m_lmcache_cleanup_threshold == 0)
      return true;
  return false;
}


void Normalize(LanguageModelIRST::weightmap_t& M)
{
  float total = 0;
  typedef LanguageModelIRST::weightmap_t::value_type entry;
  BOOST_FOREACH(entry const& e, M) {
    UTIL_THROW_IF2(e.second < 0, "Negative context weight at" << HERE);
    total += e.second;
  }
  if (total == 0) return;
  BOOST_FOREACH(entry& e, M) e.second /= total;
}

template <typename T1, typename T2>
struct less_second {
    typedef pair<T1, T2> type;

    bool operator()(type const &a, type const &b) const {
      return a.second < b.second;
    }
};

void SortAndSelect(LanguageModelIRST::weightmap_t& M, size_t limit) {
    assert(M.size() > 0);

    //check if limit (i.e the required number of weights) is smaller than the actual amount of available weights
    //if not do nothing
    if (limit < M.size()) {
        //std::map is not sortable
        //copy entries in an std::vector and sort that
        vector<pair<std::string, float> > mapcopy(M.begin(), M.end());
        //then sort the vector
        sort(mapcopy.begin(), mapcopy.end(), less_second<std::string, int>());

        //clean all entries in the original map
        M.clear();
        //then re-insert the first limit elements;
        vector<pair<std::string, float> >::const_iterator it;
        for (it = mapcopy.begin(); it != mapcopy.begin() + limit; it++) {
            M.insert(make_pair(it->first, it->second));
        }
    }else{
      //do nothing
    }
}

void LanguageModelIRST::InitializeForInput(ttasksptr const& ttask)
{
  //nothing to do
#if defined(TRACE_CACHE) && !defined(WITH_THREADS)
  m_lmtb->sentence_id++;
#endif
  // we assume here that translation is run in one single thread for each ttask
  // (no parallelization at a finer granularity involving IRSTLM)

  // This function is called prior to actual translation and allows the class
  // to set up thread-specific information such as context weights

  // DO NOT modify members of 'this' here. We are being called from different
  // threads, and there is no locking here.

  SPTR <ContextScope> const &scope = ttask->GetScope();
  bool normalize = m_weight_map_normalization;
  bool using_context_weights = false;
  SPTR < weightmap_t const> weights = scope->GetContextWeights();
//  SPTR < weightmap_t const> weights = scope->GetInterpolationWeights();
  if (!weights && m_use_context_weights) {
    normalize = true; // always normalize context weights
    weights = scope->GetContextWeights();
    using_context_weights = true;
  }
  if (weights) {
    // t_interpolation_weights is a thread_specific_ptr, change affects the local thread only
    t_interpolation_weights.reset(new weightmap_t(*weights));
//    t_interpolation_weights->reset(new weightmap_t(*weights));
    if (m_weight_map_limit > 0){ //required a specific amount of weights
      SortAndSelect(*t_interpolation_weights, m_weight_map_limit);
//      SortAndSelect(t_interpolation_weights, m_weight_map_limit);
    } 
    if (normalize){
      Normalize(*t_interpolation_weights);
//      Normalize(t_interpolation_weights);
    } 
    IFFEATUREVERBOSE(3)
    {
      typedef weightmap_t::value_type item;
      std::string weight_source = (using_context_weights ? "context weight" :
                                   "lm interpolation weight");
      BOOST_FOREACH(item const&e, *t_interpolation_weights) {
//      BOOST_FOREACH(item const&e, t_interpolation_weights) {
        ostringstream buf;
        weightmap_t::const_iterator m = weights->find(e.first);
        if (m != weights->end()) buf << m->second;
        if (normalize) buf << " => " << (*t_interpolation_weights)[e.first];
//        if (normalize) buf << " => " << (t_interpolation_weights)[e.first];
        if (m_weight_map_limit>0) buf << " => " << (*t_interpolation_weights)[e.first];
//        if (m_weight_map_limit) buf << " => " << (t_interpolation_weights)[e.first];
        TRACE_ERR("[" << GetScoreProducerDescription() << "] "
                  << weight_source << ": " << e.first << " => "
                  << buf.str() << std::endl);
      }
    }
  }
}

void LanguageModelIRST::CleanUpAfterSentenceProcessing(const InputType& source)
{
  const StaticData &staticData = StaticData::Instance();
  static int sentenceCount = 0;
  sentenceCount++;

  size_t lmcache_cleanup_threshold = staticData.GetLMCacheCleanupThreshold();

  if (LMCacheCleanup(sentenceCount, lmcache_cleanup_threshold)) {
    TRACE_ERR( "reset caches\n");
    m_lmtb->reset_caches();
  }
  t_interpolation_weights.reset();
//  t_interpolation_weights->reset();
}

void LanguageModelIRST::SetParameter(const std::string& key, const std::string& value)
{
  if (key == "id") {
    m_id = Scan<std::string>(value);
  } else if (key == "dub") {
    m_lmtb_dub = Scan<unsigned int>(value);
  } else if (key == "weight_normalization") {
    m_weight_map_normalization = Scan<bool>(value);
  } else if (key == "weight_limit") {
    m_weight_map_limit = Scan<size_t>(value);
  } else if (key == "consider-context-weights") {
    m_use_context_weights = Scan<bool>(value);
  } else {
    LanguageModelSingleFactor::SetParameter(key, value);
  }
  //m_nGramOrder   is set though LanguageModelImplementation::SetParameter   using "order" attribute 
  m_lmtb_size = m_nGramOrder;
}

}


