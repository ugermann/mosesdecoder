// $Id$
#pragma once

#include <vector>
#include "SingleFactor.h"

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
  LanguageModelMultiplexer(const std::string &line);
  ~LanguageModelMultiplexer();

  virtual void SetParameter(const std::string& key, const std::string& value);

  void Load(AllOptions::ptr const& opts);

  virtual LMResult GetValue(const std::vector<const Word*> &contextFactor, State* finalState = 0) const;

protected:
  /** Combination function to be performed on the LMs. */
  enum Function {
    INTERPOLATE_LINEAR
  };

  Function function_;  ///< combination function to be performed on the LMs
  std::string background_lm_;  ///< feature name of background LM
  std::string adaptive_lm_prefix_; ///< feature name prefix of adaptive LM, suffixed by numbers

  std::vector<FeatureFunction *> features_; ///< list of sub-LM FeatureFunctions

private:
  /** Create the wrapped sub-LMs from the moses.ini section with our name */
  void CreateSubModels();

  void initialize_features();
};


}
