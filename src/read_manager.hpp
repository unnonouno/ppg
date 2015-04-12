#ifndef READ_MANAGER_HPP_F244B187_B9DF_4A48_BEB3_4579F74FF7B3_
#define READ_MANAGER_HPP_F244B187_B9DF_4A48_BEB3_4579F74FF7B3_

#include <string>
#include <vector>

#include <pficommon/data/serialization.h>
#include <pficommon/data/serialization/unordered_map.h>
#include <pficommon/data/string/ustring.h>
#include <pficommon/data/unordered_map.h>

#include "fwd.hpp"
#include "read_normalizer.hpp"

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
  template <class Ar>
  void serialize(Ar& ar) {
    ar
        & MEMBER(uchar_to_id)
        & MEMBER(uchars)
        & MEMBER(normalize_map)
        & MEMBER(normalizer);
  }

  pfi::data::unordered_map<pfi::data::string::uchar, char_t> uchar_to_id;
  std::vector<pfi::data::string::uchar> uchars;
  pfi::data::unordered_map<char_t, char_t> normalize_map;
  ReadNormalizer normalizer;
};

}  // namespace ppg

#endif  // READ_MANAGER_HPP_F244B187_B9DF_4A48_BEB3_4579F74FF7B3_
