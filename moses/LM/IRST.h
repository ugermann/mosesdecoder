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

#ifndef moses_LanguageModelIRST_h
#define moses_LanguageModelIRST_h

#include <string>
#include <vector>

#include "moses/LM/SingleFactor.h"
#include "moses/Factor.h"
#include "moses/Hypothesis.h"
#include "moses/TypeDef.h"

#include "moses/Util.h"

#ifdef WITH_THREADS
#include <boost/thread.hpp>
#endif

//this is required because:
//- IRSTLM package uses the namespace irstlm
//- the compilation of "IRST.cpp" requires "using namespace irstlm", which is defined in any file of the IRSTLM package
//  but conflicts with these foward declaration of class lmContainer
//- for files in moses/LM the IRSTLM include directory is set
//  but not for the rest of files
#ifdef LM_IRST
class lmContainer;  // irst lm container for any lm type
class ngram;
class dictionary;
#endif


namespace Moses
{

//class LanguageModel;
class FFState;
class Phrase;

/** Implementation of single factor LM using IRST's code.
 * This is available from the same sourceforge repository
 */
class LanguageModelIRST : public LanguageModelSingleFactor
{
public:
  // the type weightmap_t  must be equal to the type topic_map_t of IRSTLM
  typedef std::map<std::string, float> weightmap_t;
  typedef std::map<std::string, weightmap_t > weightmap_map_t;

protected:
  mutable std::vector<int> m_lmIdLookup;
  lmContainer* m_lmtb;

  int m_unknownId;  //code of OOV
  int m_empty;  //code of an empty position
  int m_lmtb_sentenceStart; //lmtb symbols to initialize ngram with
  int m_lmtb_sentenceEnd;   //lmt symbol to initialize ngram with
  int m_lmtb_dub;           //dictionary upperboud
  size_t m_lmtb_size;          //max ngram stored in the table
  bool m_weight_map_normalization;  //flag to use normalized LM context weights
  size_t  m_weight_map_limit;        //number of weights to actually consider (selected after sorting)
  bool m_use_context_weights; 
  // => use context weights if no interpolation weights are given
  std::string m_id; // internal name to identify this instance of the LanguageModelIRST

  dictionary* d;

  std::string m_mapFilePath;

  void CreateFactors(FactorCollection &factorCollection);

  int GetLmID( const Word &word ) const;
  int GetLmID( const std::string &str ) const;
  int GetLmID( const Factor *factor ) const;

#ifdef WITH_THREADS
  mutable boost::shared_mutex m_lock;
  //boost::thread_specific_ptr<SPTR<weightmap_t> > t_interpolation_weights;
  boost::thread_specific_ptr<weightmap_t> t_interpolation_weights;
#else
  boost::scoped_ptr<weightmap_t> *t_interpolation_weights; 
#endif

public:
  LanguageModelIRST(const std::string &line);

  ~LanguageModelIRST();

  void SetParameter(const std::string& key, const std::string& value);

  bool IsUseable(const FactorMask &mask) const;

  void Load(AllOptions::ptr const& opts);
  const FFState *EmptyHypothesisState(const InputType &/*input*/) const;

  virtual LMResult GetValue(const std::vector<const Word*> &contextFactor, State* finalState = NULL) const;

  virtual void CalcScore(const Phrase &phrase, float &fullScore, float &ngramScore, size_t &oovCount) const;

  virtual FFState *EvaluateWhenApplied(const Hypothesis &hypo, const FFState *ps, ScoreComponentCollection *out) const;
  /*
    virtual FFState *EvaluateWhenApplied(const ChartHypothesis& cur_hypo, int featureID, ScoreComponentCollection *accumulator) const;

    virtual FFState *EvaluateWhenApplied(const Syntax::SHyperedge& hyperedge, int featureID, ScoreComponentCollection *accumulator) const;
  */

  void InitializeForInput(ttasksptr const& ttask);
  void CleanUpAfterSentenceProcessing(const InputType& source);

  void set_dictionary_upperbound(int dub) {
    m_lmtb_size=(size_t) dub ;
  };

  const std::string GetId() const {
    return m_id;
  }

  void SetId(const std::string id) {
    m_id = id;
  }

  // void print_lm_context_weights(std::string const& id);
  // void print_lm_context_weights();

};



}

#endif
