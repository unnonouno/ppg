#ifndef READ_NORMALIZER_HPP_87CD4522_83F3_4CB8_8DA7_CC5AA171162E_
#define READ_NORMALIZER_HPP_87CD4522_83F3_4CB8_8DA7_CC5AA171162E_

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

}  // namespace ppg

#endif  // READ_NORMALIZER_HPP_87CD4522_83F3_4CB8_8DA7_CC5AA171162E_
