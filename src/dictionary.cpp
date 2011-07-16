#include "dictionary.hpp"
#include "serializer.hpp"

namespace kaibun {

Dictionary Dictionary::instance;

int
Dictionary::id_of_string(const string& str) const {
  if (str_to_id.count(str) == 0) {
    id_to_str.push_back(str);
    str_to_id[str] = next_id;
    next_id++;
  }
  return str_to_id[str];
}

const string&
Dictionary::string_of_id(int id) const {
  return id_to_str[id];
}

void
Dictionary::save(OutSerializer& out) const {
  out << id_to_str << str_to_id << next_id;
}

void
Dictionary::load(InSerializer& in) {
  in >> id_to_str >> str_to_id >> next_id;
}


}
