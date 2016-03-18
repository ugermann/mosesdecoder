
#include "Multiplexer.h"
#include "moses/StaticData.h"
#include "moses/FactorCollection.h"
#include "moses/FF/Factory.h"

using namespace std;

namespace Moses
{

/**
 * Feature setup functor that just collects a list of features.
 *
 * Does not register with StaticData or FeatureFunction, so we are able to
 * manage our own list of FFs, apart from moses.
 */
class MuxFeatureSetup : public FeatureSetup {
public:
  /** Outputs data in the vector reference. */
  MuxFeatureSetup(std::vector<FeatureFunction *>& features): features_(features) {}

  virtual void operator()(FeatureFunction *feature) {
    // note: I have no understanding of FeatureFunction cleanup logic in moses. There probably is none.
    // If you do, please add appropriate cleanup logic in this class.
    // I believe that the FeatureSetup should take ownership of the FF pointer passed in.
    features_.push_back(feature);
  }
private:
  std::vector<FeatureFunction *>& features_;
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
LanguageModelMultiplexer::LanguageModelMultiplexer(const std::string &line)
  :LanguageModelSingleFactor(line)
{
  ReadParameters();
  initialize_features();

  FactorCollection &factorCollection = FactorCollection::Instance();

  // needed by parent language model classes. Why didn't they set these themselves?
  m_sentenceStart = factorCollection.AddFactor(Output, m_factorType, BOS_);
  m_sentenceStartWord[m_factorType] = m_sentenceStart;

  m_sentenceEnd		= factorCollection.AddFactor(Output, m_factorType, EOS_);
  m_sentenceEndWord[m_factorType] = m_sentenceEnd;
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

  const PARAM_VEC* params = staticData.GetParameter().GetParam(m_description); // get moses.ini section [<name>]
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


LMResult LanguageModelMultiplexer::GetValue(const vector<const Word*> &contextFactor, State* finalState) const
{
  LMResult ret;
  ret.score = contextFactor.size();
  ret.unknown = false;

  // use last word as state info
  const Factor *factor;
  size_t hash_value(const Factor &f);
  if (contextFactor.size()) {
    factor = contextFactor.back()->GetFactor(m_factorType);
  } else {
    factor = NULL;
  }

  (*finalState) = (State*) factor;

  return ret;
}

void LanguageModelMultiplexer::Load(AllOptions::ptr const &opts) {
  // we need to pass this call through to all sub-models
  for(std::vector<FeatureFunction *>::iterator it = features_.begin(); it != features_.end(); ++it)
    (*it)->Load(opts);
}

void LanguageModelMultiplexer::SetParameter(const std::string& key, const std::string& value)
{
  if (key == "function") {
    std::string function = Scan<std::string>(value);
    if(function == "interpolate-linear") {
      function_ = INTERPOLATE_LINEAR;
    } else {
      UTIL_THROW2("ERROR: invalid function name for MUXLM: '" << function << "'");
    }
  } else if (key == "background-lm") {
    background_lm_ = Scan<std::string>(value);
  } else if (key == "adaptive-lm-prefix") {
    adaptive_lm_prefix_ = Scan<std::string>(value);
  } else {
    LanguageModelSingleFactor::SetParameter(key, value);
  }
}


}



