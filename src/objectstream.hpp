#pragma once

#include "hashmap.hpp"
#include <string>
#include <vector>
#include "util.hpp"

namespace ppg {

template <typename K, typename V>
std::ostream& operator << (std::ostream& out, const ppg::hashmap<K, V>& t) {
  out << "{";
  FOREACH (e, t) {
    if (e != t.begin())
      out << ", ";
    out << e->first << ": " << e->second;
  }
  out << "}";
  return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& t) {
  out << "[";
  FOREACH (i, t) {
    if (i != t.begin())
      out << ", ";
    out << *i;
  }
  out << "]";
  return out;
}

template <typename T>
void write_pointer(std::ostream& out, const T* t) {
  if (t)
    out << *t;
  else
    out << "NULL";
}

}
