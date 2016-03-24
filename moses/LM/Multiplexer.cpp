
#include "Multiplexer.h"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <valarray>
#include <numeric>
#include <algorithm>
#include <limits>
#include <boost/math/special_functions/log1p.hpp>

#include "moses/StaticData.h"
#include "moses/Parameter.h"
#include "moses/FactorCollection.h"
#include "moses/FF/Factory.h"
#include "moses/FF/FFState.h"
#include "moses/ScoreComponentCollection.h"
#include "moses/ContextScope.h"
#include "moses/TranslationTask.h"

using namespace std;

namespace Moses
{


// useful for debugging
std::ostream& operator<<(std::ostream& os, const std::valarray<FValue>& valarr)
{
  os << "[";
  for(size_t i = 0; i < valarr.size(); i++) {
    if(i > 0)
      os << ", ";
    os << valarr[i];
  }
  os << "]";
  return os;
}


/**
 * Wraps SCC to provide a virtual GetInterpolatedScore()
 */
class Interpolator : public ScoreComponentCollection {
public:
  Interpolator(const ScoreComponentCollection& weights):
      ScoreComponentCollection(weights.getCoreFeatures().size()), m_weights(weights)
  {}

  virtual float GetInterpolatedScore() = 0;

protected:
  const ScoreComponentCollection& m_weights;
};

/**
 * Log-linear interpolation (aka dot product of scores with weights).
 */
class LogLinearInterpolator : public Interpolator {
public:
  LogLinearInterpolator(const ScoreComponentCollection& weights):
      Interpolator(weights)
  {}

  virtual float GetInterpolatedScore() {
    return GetWeightedScore(this->m_weights);
  }
};

/**
 * Linear interpolation (aka log-sum-exp, with weighted sum).
 */
class LinearLSEInterpolator : public Interpolator {
public:
  LinearLSEInterpolator(const ScoreComponentCollection& weights):
      Interpolator(weights)
  {}

  virtual float GetInterpolatedScore() {
    // log-sum-exp, with weighted sum
    const std::valarray<FValue> &scores = this->m_scores.getCoreFeatures();
    const std::valarray<FValue> &weights = this->m_weights.getCoreFeatures();

    std::valarray<FValue> raised = std::exp(scores);
    std::valarray<FValue> weighted = raised * weights;

    // note: should we use double throughout?

    // the log-sum-exp trick:
    // assume x >> y. log(exp(x) + exp(y)) = log(exp(x) * (1 + exp(y)/exp(x))) = x + log(1 + exp(y-x))
    //
    // for us in the weighted case:
    // assume x >> y. log(a*exp(x) + b*exp(y)) = log(a*exp(x) * (1 + b*exp(y)/exp(x)/a)) = log(a) + x + log(1 + b/a*exp(y-x))

    // find the max index: distance(A, max_element(A, A + N))
    size_t imax = -1;
    float emax = std::numeric_limits<float>::min();
    for(size_t i = 0; i < weighted.size(); i++) {
      if(weighted[i] > emax) {
        emax = weighted[i];
        imax = i;
      }
    }
    std::valarray<FValue> diff_raised = std::exp(scores - scores[imax]);
    std::valarray<FValue> diff_raised_weighted = diff_raised * weights / weights[imax];

    // debug: sanity assertions
    for(size_t i = 0; i < weights.size(); i++)
      UTIL_THROW_IF2(weights[i] < 0.0, "MUXLM: assert failed: weights[" << i << "] >= 0.0");
    for(size_t i = 0; i < diff_raised.size(); i++)
      UTIL_THROW_IF2(diff_raised[i] < 0.0, "MUXLM: assert failed: diff_raised[" << i << "] >= 0.0");
    for(size_t i = 0; i < diff_raised_weighted.size(); i++)
      UTIL_THROW_IF2(diff_raised_weighted[i] < 0.0, "MUXLM: assert failed: diff_raised_weighted[" << i << "] >= 0.0");
    UTIL_THROW_IF2(weights.size() != diff_raised.size(), "MUXLM: assert failed: weights.size() == diff_raised.size()");
    UTIL_THROW_IF2(diff_raised_weighted.size() != diff_raised.size(), "MUXLM: assert failed: diff_raised_weighted.size() == diff_raised.size()");
    // debug: end sanity assertions

    float in_product = 0.0;
    // since we are using log1p, avoid adding the max element itself, which a/a*exp(x-x) == 1.0
    // compute in_product = b/a*exp(y-x) + ...
    for(size_t i = 0; i < diff_raised_weighted.size(); i++)
      if(i != imax)
        in_product += diff_raised_weighted[i];
    UTIL_THROW_IF2(in_product < 0.0, "MUXLM: assert failed: in_product >= 0.0"); // DEBUG only
    float interpolated = log(weights[imax]) + scores[imax] + boost::math::log1p(in_product);

    return interpolated;
  }
};

class LinearPlainInterpolator : public Interpolator {
public:
  LinearPlainInterpolator(const ScoreComponentCollection& weights):
      Interpolator(weights)
  {}

  virtual float GetInterpolatedScore() {
    const std::valarray<FValue> &scores = this->m_scores.getCoreFeatures();
    const std::valarray<FValue> &weights = this->m_weights.getCoreFeatures();

    std::valarray<FValue> raised = std::exp(scores);
    std::valarray<FValue> weighted = raised * weights;

    float s = weighted.sum();

    UTIL_THROW_IF2(s == 0.0, "MUXLM: weighted.sum() must not be 0");
    return log(s);
  }
};


void LanguageModelMultiplexer::InitializeForInput(ttasksptr const& ttask)
{
  // this is called from several different threads and hence it must be thread-safe.
  weights_.reset(new Weights(features_.size()));
  std::vector<float> new_weights;
  Weights& weights = *weights_.get();

  // also, I would like two weights to be tuned.
  // hack: add one weight, which we always output as 0 to moses, but ask for the value and use it ourselves.
  const StaticData& staticData = StaticData::Instance();

  // (1-alpha) * P_background + alpha * P_adaptive -- see docstring for this->alpha_

  // obtain domain weights
  std::map<std::string, float> weight_map;
  SPTR<std::map<std::string, float> const> w = ttask->GetScope()->GetContextWeights();
  if(w && !w->empty()) {
    // bias weights specified with the session
    for(std::map<std::string, float>::const_iterator it = w->begin(); it != w->end(); ++it)
      weight_map.insert(*it);
  } else {
    // fall back to uniform weights
    for(std::vector<LanguageModel *>::iterator it = adaptive_.begin(); it != adaptive_.end(); ++it)
      weight_map[(*it)->GetScoreProducerDescription()] = 1.0;
    XVERBOSE(1, "MUXLM: no context weights, uniform weight fallback.\n");
  }
  normalize_weights(weight_map, alpha_); // normalize sum to alpha_

  // first feature is background LM
  XVERBOSE(2, "MUXLM: weight_background = " << (1.0f - alpha_) << "\n");
  new_weights.push_back(1.0f - alpha_);
  // next features are adaptive LMs
  for(size_t i = 0; i < adaptive_.size(); i++) {
    XVERBOSE(2, "MUXLM: weight[" << adaptive_[i]->GetScoreProducerDescription() << "] = " << weight_map[adaptive_[i]->GetScoreProducerDescription()] << "\n");
    new_weights.push_back(weight_map[adaptive_[i]->GetScoreProducerDescription()]);
  }
  weights.Assign((size_t) 0, new_weights);
}


/**
 * A container for all our sub-LM states.
 */
struct MuxLMState : public FFState {
  size_t num_states;
  FFState **states; ///< always at least length 1, background LM state is first

  MuxLMState(size_t nstates): num_states(nstates) {
    assert(nstates >= 1);
    states = new FFState*[nstates];
    memset(states, 0, sizeof(FFState*) * nstates);
    // individual states are allocated later, externally.
  }

  virtual ~MuxLMState() {
    for(size_t i = 0; i < num_states; i++)
      if(states[i] != NULL)
        delete states[i];
    delete states;
  }

  virtual size_t hash() const {
    // we only hash the background LM state (see argumentation below)
    return states[0]->hash();
  }

  virtual bool operator==(const FFState& o) const {
    // we only compare the background LM state, since that should be sufficient for recombination
    // TODO: (unless somebody prunes it more than the other LMs ...)
    const MuxLMState &other = static_cast<const MuxLMState &>(o);
    return *states[0] == *other.states[0];
  }
};


/**
 * Feature setup functor that just collects a list of features.
 *
 * Does not register with StaticData or FeatureFunction, so we are able to
 * manage our own list of FFs, apart from moses.
 */
class MuxFeatureSetup : public FeatureSetup {
public:
  /** Outputs data in the vector reference. */
  MuxFeatureSetup(std::vector<LanguageModel *>& features): features_(features) {}

  virtual void operator()(FeatureFunction *feature) {
    // TODO: I have no understanding of FeatureFunction cleanup logic in moses.
    // If you do, please add appropriate cleanup logic in this class.
    // I believe that the FeatureSetup should take ownership of the FF pointer passed in.
    features_.push_back(static_cast<LanguageModel *>(feature));
  }
private:
  std::vector<LanguageModel *>& features_;
};


/*
 * General loading strategy:
 *
 * * LanguageModelMultiplexer()
 *     ReadParameters() reads MUXLM feature line params, including name=
 *     initialize_features() reads feature lines for sub-LMs from the [<name>] section in moses.ini,
 *                       creates individual LM objects for those lines
 * * Load() called by moses after all FFs have been created
 *     call passed on to Load() of sub-LMs, which actually load up model files from disk
 */
LanguageModelMultiplexer::LanguageModelMultiplexer(const std::string &line, bool registerNow)
  : LanguageModelSingleFactor(line), function_(INTERPOLATE_LINEAR), alpha_(0.5), background_(NULL)
{
  ReadParameters();
  initialize_features(); // loads this->features_

  // separate background and adaptive LMs
  for(std::vector<LanguageModel *>::iterator it = features_.begin(); it != features_.end(); ++it) {
    if((*it)->GetScoreProducerDescription() == background_lm_)
      background_ = *it;
    else
      adaptive_.push_back(*it);
  }
  UTIL_THROW_IF2(background_ == NULL, "MUXLM ERROR: no background LM was specified.");
  // reorder to make background_ the first in features_
  features_.clear();
  features_.push_back(background_);
  features_.insert(features_.end(), adaptive_.begin(), adaptive_.end());
}

LanguageModelMultiplexer::~LanguageModelMultiplexer()
{
}


// this is almost a straight copy of StaticData::initialize_features(), but uses a different
// moses.ini section name ([<name>] instead of [feature], where <name> is MUXLM name= parameter),
// and a different FeatureSetup for the FeatureRegistry, so our sub-features are not registered with moses.
// TODO: how to unify these? Maybe initialize_features() could be moved to FeatureRegistry (from StaticData and here).
void
LanguageModelMultiplexer::initialize_features()
{
  const StaticData& staticData = StaticData::Instance();
  std::map<std::string, std::string> featureNameOverride = staticData.OverrideFeatureNames();
  // all features
  map<string, int> featureIndexMap;
  SPTR<MuxFeatureSetup> setup(new MuxFeatureSetup(this->features_)); // fills this->features_ with the created FF objects.
  FeatureRegistry registry(setup);

  /*
   * Unfortunately, the way the Parameter parser works on moses.ini, we verify that each section name
   * is a valid parameter. We could either lift that restriction (and potentially make misspelled sections
   * have no effect), or we could add to Parameter::m_valid dynamically after having parsed the MUXLM feature
   * line (which makes the [<name>] section valid, but only *after* [feature] having defined the MUXLM...
   *
   * Since neither of these options is very satisfying, I will hardcode a maximum of one of MUXLM.
   */
  UTIL_THROW_IF2(m_description != "muxlm", "MUXLM must have name=muxlm, and only one of this feature is allowed.");

  // note: ideally, we should be able to parse an INI file without checking for moses parameters... herp derp duh.
  Moses::Parameter config;
  bool success = config.LoadParam(this->m_filePath);
  UTIL_THROW_IF2(!success, "MUXLM failed to load path=" << this->m_filePath);

  const PARAM_VEC* params = config.GetParam(m_description); // get moses.ini section [<name>]
  for (size_t i = 0; params && i < params->size(); ++i) {
    const string &line = Trim(params->at(i));
    VERBOSE(1,"line=" << line << endl);
    if (line.empty())
      continue;

    vector<string> toks = Tokenize(line);

    string &feature = toks[0];
    std::map<std::string, std::string>::const_iterator iter
        = featureNameOverride.find(feature);
    if (iter == featureNameOverride.end()) {
      // feature name not override
      registry.Construct(feature, line);
    } else {
      // replace feature name with new name
      string newName = iter->second;
      feature = newName;
      string newLine = Join(" ", toks);
      registry.Construct(newName, newLine);
    }
  }

  //NoCache();  // only in StaticData: only deals with PhraseTables. We only care about LMs here.
  //staticData.OverrideFeatures();  // I don't know the effect of overriding twice, but it probably re-processes ...
  // ... already changed features, so that is not a good idea. Who uses this anyway?
}

void LanguageModelMultiplexer::Load(AllOptions::ptr const &opts) {
  // we need to pass this call through to all sub-models
  for (size_t i = 0; i < features_.size(); i++) {
    UTIL_THROW_IF2(features_[i]->GetNumScoreComponents() != 1, "MUXLM only supports FFs with 1 score component");
    features_[i]->SetIndex(i);
    features_[i]->Load(opts);
  }

  // check some bounds for alpha
  XVERBOSE(2, "MUXLM: alpha = " << alpha_ << "\n");
  UTIL_THROW_IF2(alpha_ < 0.0, "MUXLM: alpha weight must be from range [0, 1)");
  UTIL_THROW_IF2(alpha_ > 1.0f, "MUXLM: alpha weight must be from range [0, 1)");
}

void LanguageModelMultiplexer::SetParameter(const std::string& key, const std::string& value)
{
  if (key == "function") {
    std::string function = Scan<std::string>(value);
    if(function == "interpolate-log-linear") {
      function_ = INTERPOLATE_LOG_LINEAR;
    } else if(function == "interpolate-linear") {
      function_ = INTERPOLATE_LINEAR;
    } else if(function == "interpolate-plain-linear") {
      function_ = INTERPOLATE_PLAIN_LINEAR;
    } else {
      UTIL_THROW2("ERROR: invalid function name for MUXLM: '" << function << "'");
    }
  } else if (key == "alpha") {
    alpha_ = Scan<float>(value);
  } else if (key == "background-lm") {
    background_lm_ = Scan<std::string>(value);
  } else {
    LanguageModelSingleFactor::SetParameter(key, value);
  }
}

Interpolator* LanguageModelMultiplexer::CreateInterpolator() const
{
  const Weights& weights = *weights_.get(); // thread-specific weights

  switch(function_) {
    case INTERPOLATE_LINEAR:
      return new LinearLSEInterpolator(weights);
    case INTERPOLATE_LOG_LINEAR:
      return new LogLinearInterpolator(weights);
    case INTERPOLATE_PLAIN_LINEAR:
      return new LinearPlainInterpolator(weights);
    default:
      UTIL_THROW2("MUXLM: invalid function_ value.");
  }
}

//////////////////////////////////////////////////////////////////////////////////

FFState* LanguageModelMultiplexer::EvaluateWhenApplied(
    const ChartHypothesis& /* cur_hypo */,
    int /* featureID - used to index the state in the previous hypotheses */,
    ScoreComponentCollection* accumulator) const
{
  UTIL_THROW2("MUXLM does not yet implement EvaluateWhenApplied(ChartHypothesis&, ...)");
  return NULL;
}


const FFState* LanguageModelMultiplexer::EmptyHypothesisState(const InputType &input) const
{
  MuxLMState *state = new MuxLMState(features_.size());
  for(size_t i = 0; i < state->num_states; i++)
    state->states[i] = const_cast<FFState*>(features_[i]->EmptyHypothesisState(input));
  return state;
}

void
LanguageModelMultiplexer::
EvaluateInIsolation(Phrase const& source, TargetPhrase const& targetPhrase,
                    ScoreComponentCollection &scoreBreakdown,
                    ScoreComponentCollection &estimatedScores) const
{
  // this is almost identical to LanguageModel::EvaluateInIsolation(), except for the additional feature[1]
  // (which always provides 0 score, but we use its weight elsewhere)

  VERBOSE(2,"void LanguageModelMultiplexer::EvaluateInIsolation(const Phrase &source, const TargetPhrase &targetPhrase, ...)" << std::endl);
  // contains factors used by this LM
  float fullScore, nGramScore;
  size_t oovCount;

  VERBOSE(2,"targetPhrase:|" << targetPhrase << "|" << std::endl);
  VERBOSE(2,"pthread_self():" << pthread_self() << endl);

  CalcScore(targetPhrase, fullScore, nGramScore, oovCount);

  float estimateScore = fullScore - nGramScore;

  if (m_enableOOVFeature) {
    UTIL_THROW2("MUXLM: OOVFeature is not implemented yet");
  } else {
    scoreBreakdown.Assign(this, nGramScore);
    estimatedScores.Assign(this, estimateScore);

    VERBOSE(2,"CalcScore of targetPhrase:|" << targetPhrase << "|: ngr=" << nGramScore << " est=" << estimateScore << std::endl);
  }
}


void LanguageModelMultiplexer::CalcScore(const Phrase &phrase, float &fullScore, float &ngramScore, std::size_t &oovCount) const
{
  Weights& weights = *weights_.get(); // thread-specific weights

  boost::scoped_ptr<Interpolator> fullScores(CreateInterpolator());
  boost::scoped_ptr<Interpolator> ngramScores(CreateInterpolator());

  oovCount = phrase.GetSize();

  float full, ngram;
  size_t oovs;
  for(size_t i = 0; i < features_.size(); i++) {
    features_[i]->CalcScore(phrase, full, ngram, oovs);
    fullScores->Assign(i, full);
    ngramScores->Assign(i, ngram);
    oovCount = std::min(oovs, oovCount);
  }

  fullScore = fullScores->GetInterpolatedScore();
  ngramScore = ngramScores->GetInterpolatedScore();
}

FFState* LanguageModelMultiplexer::EvaluateWhenApplied(const Hypothesis &hypo, const FFState *ps, ScoreComponentCollection *out) const
{
  Weights& weights = *weights_.get(); // thread-specific weights
  const MuxLMState &in_state = static_cast<const MuxLMState&>(*ps);
  MuxLMState *ret = new MuxLMState(features_.size());

  if(!hypo.GetCurrTargetLength()) {
    *ret = in_state;
    return ret;
  }

  boost::scoped_ptr<Interpolator> score(CreateInterpolator());
  for(size_t i = 0; i < features_.size(); i++) {
    ret->states[i] = features_[i]->EvaluateWhenApplied(hypo, in_state.states[i], score.get());
  }

  if(OOVFeatureEnabled()) {
    UTIL_THROW2("OOV feature is not implemented yet");
  }
  out->PlusEquals(this, score->GetInterpolatedScore());

  //XVERBOSE(2, "MUXLM total score[" << this->GetIndex() << "] = " << out->GetScoresVector()[this->GetIndex() + 0] << "\n");

  return ret;
}

void LanguageModelMultiplexer::normalize_weights(std::map<std::string, float>& map, float alpha)
{
  std::map<std::string, float> ret;
  float total = 0.0;

  for(std::map<std::string, float>::iterator it = map.begin(); it != map.end(); ++it)
    total += it->second;

  if(total == 0.0)
    total = 1.0f;

  for(std::map<std::string, float>::iterator it = map.begin(); it != map.end(); ++it)
    ret[it->first] = it->second * alpha / total;

  // replace map contents
  map.clear();
  map.insert(ret.begin(), ret.end());
}

void LanguageModelMultiplexer::CleanUpAfterSentenceProcessing(const InputType& source)
{
  // this is called from several different threads and hence it must be thread-safe.
  weights_.reset(NULL);
}

bool LanguageModelMultiplexer::IsUseable(const FactorMask &mask) const
{
  bool ret = mask[m_factorType];
  return ret;
}

LMResult LanguageModelMultiplexer::GetValue(const vector<const Word*> &contextFactor, State* finalState) const
{
  UTIL_THROW2("MUXLM does not implement GetValue()");
  LMResult result;
  result.unknown = false;
  result.score = 0.0;
  return result;
}

}



