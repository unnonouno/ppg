#include "read_manager.hpp"

using namespace std;
using pfi::data::string::ustring;
using pfi::data::string::uchar;

namespace ppg {

read_t ReadManager::string_to_read(const string& str) {
  return ustring_to_read(pfi::data::string::string_to_ustring(str));
}

read_t ReadManager::ustring_to_read(const ustring& ustr) {
  read_t r;
  for (size_t i = 0; i < ustr.size(); ++i) {
    r.push_back(uchar_to_char(ustr[i]));
  }
  return r;
}

char_t ReadManager::uchar_to_char(uchar ch) {
  ch = normalizer.normalizeChar(ch);
  if (uchar_to_id.count(ch) == 0) {
    char_t id = uchars.size();
    uchars.push_back(ch);
    return uchar_to_id[ch] = id;
  } else {
    return uchar_to_id[ch];
  }
}

uchar ReadManager::char_to_uchar(char_t ch) {
  return uchars[ch];
}

ustring ReadManager::read_to_ustring(const read_t& read) {
  ustring str;
  for (size_t i = 0; i < read.size(); ++i) {
    str += uchars[read[i]];
  }
  return str;
}

string ReadManager::read_to_string(const read_t& read) {
  return pfi::data::string::ustring_to_string(read_to_ustring(read));
}

}
