#include "util.hpp"

#include <sstream>
#include <vector>

namespace ppg {

using namespace std;

vector<char_t> str_to_read(const string& s) {
  vector<char_t> v;

  FOREACH (c, s)
    v.push_back(*c);
  return v;
}

string read_to_str(const read_t& r) {
  stringstream s;

  FOREACH (it, r)
    s << (*it) << "-";
  return s.str();
}

}
