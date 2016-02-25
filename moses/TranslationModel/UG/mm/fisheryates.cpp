/**
 * This file is part of moses.  Its use is licensed under the GNU Lesser General
 * Public License version 2.1 or, at your option, any later version.
 */

#include "fisheryates.h"

namespace map_helper {
  size_t get(boost::unordered_map<size_t, size_t> m, size_t key) {
    size_t defaultVal = key;
    boost::unordered_map<size_t, size_t>::iterator it = m.find(key);
    if(it != m.end())
      return it->second;
    else
      return defaultVal;
  }
}
