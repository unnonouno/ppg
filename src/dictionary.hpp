#ifndef DICTIONARY_HPP_5E25FCC3_50CF_45AB_89AC_7F4F43FFFFFC_
#define DICTIONARY_HPP_5E25FCC3_50CF_45AB_89AC_7F4F43FFFFFC_

#include <string>
#include <vector>

#include <pficommon/data/unordered_map.h>
#include <pficommon/data/serialization.h>

#include "fwd.hpp"

namespace ppg {

class Dictionary {
 public:
  id_t id_of_string(const std::string& str) const;

  const std::string& string_of_id(id_t id) const;

 private:
  friend class pfi::data::serialization::access;

  template <class Ar>
  void serialize(Ar &ar) {
    ar
        & MEMBER(id_to_str)
        & MEMBER(str_to_id);
  }

  mutable std::vector<std::string> id_to_str;
  mutable pfi::data::unordered_map<std::string, id_t> str_to_id;
};

}  // namespace ppg

#endif  // DICTIONARY_HPP_5E25FCC3_50CF_45AB_89AC_7F4F43FFFFFC_
