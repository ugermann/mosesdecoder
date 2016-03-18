// $Id$
#pragma once

#include <vector>
#include "SingleFactor.h"

namespace Moses
{

class LanguageModelMultiplexer : public LanguageModelSingleFactor
{
protected:

public:
  LanguageModelMultiplexer(const std::string &line);
  ~LanguageModelMultiplexer();

  virtual LMResult GetValue(const std::vector<const Word*> &contextFactor, State* finalState = 0) const;
};


}
