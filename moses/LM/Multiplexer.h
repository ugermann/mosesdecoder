// $Id$
#pragma once

#include <boost/thread.hpp>
#include <vector>
#include <map>

#include "SingleFactor.h"
#include "Base.h"

namespace Moses
{

/**
 * A wrapper class for several language models of any type. Enables various interpolation functions.
 *
 * @author David Madl <git@abanbytes.eu>
 */
class LanguageModelMultiplexer : public LanguageModelSingleFactor
{
public:
  LanguageModelMultiplexer(const std::string &line, bool registerNow = true);
  ~LanguageModelMultiplexer();

  virtual void SetParameter(const std::string& key, const std::string& value);

  void Load(AllOptions::ptr const& opts);

  //virtual LMResult GetValue(const std::vector<const Word*> &contextFactor, State* finalState = 0) const;

  virtual const FFState* EmptyHypothesisState(const InputType &input) const;

  virtual void EvaluateInIsolation(const Phrase &source
                                   , const TargetPhrase &targetPhrase
                                   , ScoreComponentCollection &scoreBreakdown
                                   , ScoreComponentCollection &estimatedScores) const;

  virtual void CalcScore(const Phrase &phrase, float &fullScore, float &ngramScore, std::size_t &oovCount) const;

  virtual FFState *EvaluateWhenApplied(const Hypothesis &hypo, const FFState *ps, ScoreComponentCollection *out) const;

  virtual FFState* EvaluateWhenApplied(
      const ChartHypothesis& /* cur_hypo */,
      int /* featureID - used to index the state in the previous hypotheses */,
      ScoreComponentCollection* accumulator) const;

  ///////

  /** Called before actual translation of a sentence. Thread-safe. */
  void InitializeForInput(ttasksptr const& ttask);
  /** Called after translation of a sentence. Thread-safe. */
  void CleanUpAfterSentenceProcessing(const InputType& source);

  virtual bool IsUseable(const FactorMask &mask) const;

  // dummy for LanguageModelSingleFactor
  virtual LMResult GetValue(const std::vector<const Word*> &contextFactor, State* finalState = NULL) const;

protected:
  /** Combination function to be performed on the LMs. */
  enum Function {
    INTERPOLATE_LOG_LINEAR,
    INTERPOLATE_LINEAR
  };

  Function function_;  ///< combination function to be performed on the LMs
  std::string background_lm_;  ///< feature name of background LM

  boost::thread_specific_ptr<std::vector<float> > weights_; ///< feature weights, specified dynamically for each sentence
  std::vector<LanguageModel *> features_; ///< list of sub-LM FeatureFunctions

  LanguageModel* background_; ///< background LM
  std::vector<LanguageModel *> adaptive_; ///< adaptive LMs

private:
  /** Create the wrapped sub-LMs from the moses.ini section with our name */
  void CreateSubModels();

  void initialize_features();

  /** normalize the provided weights map to sum to alpha */
  void normalize_weights(std::map<std::string, float>& map, float alpha = 1.0);
};


}
