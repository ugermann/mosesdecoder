// -*- mode: c++; indent-tabs-mode: nil; tab-width: 2 -*-
// A class to store "local" information (such as task-specific caches).
// The idea is for each translation task to have a scope, which stores
// shared pointers to task-specific objects such as caches and priors.
// Since these objects are referenced via shared pointers, sopes can
// share information.
#pragma once

#ifdef WITH_THREADS
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/foreach.hpp>
#endif

// for some reason, the xmlrpc_c headers must be included AFTER the
// boost thread-related ones ...
#include "xmlrpc-c.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include "TypeDef.h"
#include "Util.h"

#include "StaticData.h"
#include "ScoreComponentCollection.h"
#include "FF/FeatureFunction.h"

namespace Moses
{

class ContextScope
{
protected:
  typedef std::map<void const*, boost::shared_ptr<void> > scratchpad_t;
  typedef scratchpad_t::iterator iter_t;
  typedef scratchpad_t::value_type entry_t;
  typedef scratchpad_t::const_iterator const_iter_t;
  scratchpad_t m_scratchpad;
#ifdef WITH_THREADS
  mutable boost::shared_mutex m_lock;
#endif
  SPTR< std::map<std::string,float> const> m_context_weights;
  SPTR< std::map<std::string,float> const> m_lm_interpolation_weights;
  SPTR< std::map<std::string, std::vector<float> > const> m_feature_weights;
  ScoreComponentCollection m_feature_weights_scc;
public:
  typedef boost::shared_ptr<ContextScope> ptr;
  template<typename T>
  boost::shared_ptr<void> const&
  set(void const* const key, boost::shared_ptr<T> const& val) {
#ifdef WITH_THREADS
    boost::unique_lock<boost::shared_mutex> lock(m_lock);
#endif
    return (m_scratchpad[key] = val);
  }

  template<typename T>
  boost::shared_ptr<T> const
  get(void const* key, bool CreateNewIfNecessary=false) {
#ifdef WITH_THREADS
    using boost::shared_mutex;
    using boost::upgrade_lock;
    upgrade_lock<shared_mutex> lock(m_lock);
#endif
    iter_t m = m_scratchpad.find(key);
    boost::shared_ptr< T > ret;
    if (m != m_scratchpad.end()) {
      if (m->second == NULL && CreateNewIfNecessary) {
#ifdef WITH_THREADS
        boost::upgrade_to_unique_lock<shared_mutex> xlock(lock);
#endif
        m->second.reset(new T);
      }
      ret = boost::static_pointer_cast< T >(m->second);
      return ret;
    }
    if (!CreateNewIfNecessary) return ret;
#ifdef WITH_THREADS
    boost::upgrade_to_unique_lock<shared_mutex> xlock(lock);
#endif
    ret.reset(new T);
    m_scratchpad[key] = ret;
    return ret;
  }

  ContextScope() {
    m_feature_weights_scc = StaticData::Instance().GetAllWeights();
  }

  ContextScope(ContextScope const& other) {
#ifdef WITH_THREADS
    boost::unique_lock<boost::shared_mutex> lock1(this->m_lock);
    boost::unique_lock<boost::shared_mutex> lock2(other.m_lock);
#endif
    m_scratchpad = other.m_scratchpad;
  }

  SPTR<std::map<std::string,float> const> const&
  GetContextWeights() {
    return m_context_weights;
  }
  
  SPTR<std::map<std::string,float> const> const&
  GetLmInterpolationWeights() {
    return m_lm_interpolation_weights;
  }

  std::map<std::string,float>*
  CreateWeightMap(std::string const& spec) {
   std::map<std::string,float>* M = new std::map<std::string,float>;
   
   std::vector<std::string> tokens = Tokenize(spec,",");
   for (std::vector<std::string>::iterator it = tokens.begin();
        it != tokens.end(); it++) {
     std::vector<std::string> key_and_value = Tokenize(*it, ":");
     (*M)[key_and_value[0]] = atof(key_and_value[1].c_str());
   }
   return M;
 }

  bool
  SetContextWeights(std::string const& spec) {
    if (m_context_weights) return false;
    // You can set the weights only once during the lifetime of a
    // ContextScope object!
#ifdef WITH_THREADS
    boost::unique_lock<boost::shared_mutex> lock(m_lock);
#endif
    // may have changed while we waited for the lock
    if (m_context_weights) return false;
    m_context_weights.reset(CreateWeightMap(spec));
    return true;
  }

  bool
  SetLmInterpolationWeights(std::string const& spec) {
    if (m_lm_interpolation_weights) return false;
    // You can set the weights only once during the lifetime of a
    // ContextScope object!
#ifdef WITH_THREADS
    boost::unique_lock<boost::shared_mutex> lock(m_lock);
#endif
    // may have changed while we waited for the lock
    if (m_lm_interpolation_weights) return false;
    m_lm_interpolation_weights.reset(CreateWeightMap(spec));
    return true;
  }

  bool
  SetContextWeights(SPTR<std::map<std::string,float> const> const& w) {
    if (m_context_weights) return false;
#ifdef WITH_THREADS
    boost::unique_lock<boost::shared_mutex> lock(m_lock);
#endif
    // may have changed while we waited for the lock
    if (m_context_weights) return false;
    m_context_weights = w;
    return true;
  }

  bool
  SetLmInterpolationWeights(SPTR<std::map<std::string,float> const> const& w) {
    if (m_lm_interpolation_weights) return false;
#ifdef WITH_THREADS
    boost::unique_lock<boost::shared_mutex> lock(m_lock);
#endif
    // may have changed while we waited for the lock
    if (m_lm_interpolation_weights) return false;
    m_lm_interpolation_weights = w;
    return true;
  }

  bool
  SetFeatureWeights(SPTR< std::map<std::string, std::vector<float> > const> const& w) {
    if (m_feature_weights) return false;
#ifdef WITH_THREADS
    boost::unique_lock<boost::shared_mutex> lock(m_lock);
#endif
    // may have changed while we waited for the lock
    if (m_feature_weights) return false;
    m_feature_weights = w;

    // note the locked state of affairs when replacing SetFeatureWeights()
    SetFeatureWeightsScc(*m_feature_weights);

    return true;
  }

  const ScoreComponentCollection& GetFeatureWeights() const {
    return m_feature_weights_scc;
  }

private:
  void SetFeatureWeightsScc(const std::map<std::string, std::vector<float> >& weights) {
    std::vector<FeatureFunction*>::const_iterator ff;
    const std::vector<FeatureFunction*>& ffs = FeatureFunction::GetFeatureFunctions();
    for(ff = ffs.begin(); ff != ffs.end(); ++ff) {
      const std::string &featureName = (*ff)->GetScoreProducerDescription();
      std::map<std::string, std::vector<float> >::const_iterator entry = weights.find(featureName);
      UTIL_THROW_IF2(entry == weights.end(), "ContextScope::SetFeatureWeights(): missing a feature weight for " << featureName);
      m_feature_weights_scc.Assign(*ff, entry->second);
    }
  }
};

};
