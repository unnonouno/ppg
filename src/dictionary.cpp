#include "dictionary.hpp"

#include <cassert>
#include <string>

namespace ppg {

id_t
Dictionary::id_of_string(const std::string& str) const {
  if (str_to_id.count(str) == 0) {
    str_to_id[str] = id_to_str.size();
    id_to_str.push_back(str);
  }
  return str_to_id[str];
}

const std::string&
Dictionary::string_of_id(id_t id) const {
  assert(id < id_to_str.size());
  return id_to_str[id];
}

}  // namespace ppg
