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

namespace kaibun {

using namespace std;

vector<char_t> str_to_read(const string&);
string read_to_str(const read_t&);


}

using namespace std;
template <typename T>
ostream& operator << (ostream& out, const vector<T>& v) {
  out << "[";
  FOREACH (x, v) {
    if (x != v.begin())
      out << ';';
    out << *x;
  }
  out << "]";
  return out;
}

namespace boost { 
namespace serialization {

template<class Archive, class T1, class T2>
inline void serialize(Archive & ar,
                      std::pair<T1, T2> &p,
                      const unsigned int file_version) {
  ar & p.first & p.second;
}
}

}
