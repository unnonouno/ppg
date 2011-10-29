#pragma once

#include "fwd.hpp"
#include <vector>
#include <string>
#include <iostream>

#define STR(s) \
  (sstream() << s).str()


#define FOREACH(it, col)                                                \
  for (typeof(col.begin()) it = col.begin(); it != col.end(); ++it)

#define FOREACH_REV(it, col)                                            \
  for (typeof(col.rbegin()) it = col.rbegin(); it != col.rend(); ++it)

namespace ppg {

std::vector<char_t> str_to_read(const std::string&);
std::string read_to_str(const read_t&);

}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& v) {
  out << "[";
  FOREACH (x, v) {
    if (x != v.begin())
      out << ';';
    out << *x;
  }
  out << "]";
  return out;
}

