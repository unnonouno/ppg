#include "dictionary.hpp"

#include <string>

namespace ppg {

Dictionary Dictionary::instance;

int
Dictionary::id_of_string(const std::string& str) const {
  if (str_to_id.count(str) == 0) {
    id_to_str.push_back(str);
    str_to_id[str] = next_id;
    next_id++;
  }
  return str_to_id[str];
}

const std::string&
Dictionary::string_of_id(int id) const {
  return id_to_str[id];
}

}  // namespace ppg
