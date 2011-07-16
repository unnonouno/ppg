#pragma once

#include "fwd.hpp"
#include <vector>
#include "hashmap.hpp"
#include "serializer.hpp"

namespace kaibun {

using namespace std;

class Dictionary {
public:
  static Dictionary& inst() { return instance; }

  int id_of_string(const string& str) const;

  const string& string_of_id(int id) const;

  void save(OutSerializer&) const;
  void load(InSerializer&);

private:
  static Dictionary instance;

  mutable vector<string> id_to_str;
  mutable hashmap<string, int> str_to_id;
  mutable int next_id;
};

}
