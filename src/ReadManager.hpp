#pragma once

#include <string>
#include <pficommon/data/string/ustring.h>
#include <pficommon/data/unordered_map.h>
#include <pficommon/data/serialization.h>
#include <pficommon/data/serialization/unordered_map.h>
#include <vector>

#include "fwd.hpp"
#include "ReadNormalizer.hpp"

namespace ppg {

class ReadManager {
 public:
  read_t string_to_read(const std::string& str);

  read_t ustring_to_read(const pfi::data::string::ustring& ustr);

  char_t uchar_to_char(pfi::data::string::uchar ch);

  pfi::data::string::uchar char_to_uchar(char_t ch);

  pfi::data::string::ustring read_to_ustring(const read_t& read);

  std::string read_to_string(const read_t& read);

 private:
  friend class pfi::data::serialization::access;
  template <class A>
  void serialize(A &a) {
    a & uchar_to_id & uchars & normalize_map & normalizer;
  }

  pfi::data::unordered_map<pfi::data::string::uchar, char_t> uchar_to_id;
  std::vector<pfi::data::string::uchar> uchars;
  pfi::data::unordered_map<char_t, char_t> normalize_map;
  ReadNormalizer normalizer;
};

}
