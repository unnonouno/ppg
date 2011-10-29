#pragma once

#include <pficommon/data/string/ustring.h>
#include <pficommon/data/unordered_map.h>
#include <pficommon/data/serialization.h>

#include "fwd.hpp"

namespace ppg {

class ReadNormalizer {
 public:
  typedef pfi::data::string::uchar uchar_t;

  ReadNormalizer();

  uchar_t normalizeChar(uchar_t ch) const;
  
 private:
  friend class pfi::data::serialization::access;
  template <class A>
  void serialize(A &a) {
    a & normalize_map;
  }

  typedef pfi::data::unordered_map<uchar_t, uchar_t> map_t;
  
  map_t normalize_map;
};


}
