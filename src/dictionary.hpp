#pragma once

#include "fwd.hpp"
#include <vector>
#include <pficommon/data/unordered_map.h>
#include <pficommon/data/serialization.h>

namespace ppg {

class Dictionary {
public:
  static Dictionary& inst() { return instance; }

  int id_of_string(const std::string& str) const;

  const std::string& string_of_id(int id) const;

private:
  static Dictionary instance;

  friend class pfi::data::serialization::access;

  template <class A>
  void serialize(A &a) {
    a & id_to_str & str_to_id & next_id;
  }

  mutable std::vector<std::string> id_to_str;
  mutable pfi::data::unordered_map<std::string, int> str_to_id;
  mutable int next_id;
};

}
