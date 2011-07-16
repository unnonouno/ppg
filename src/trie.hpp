#pragma once

#include "fwd.hpp"
#include <string>

#include "serializer.hpp"

namespace kaibun {

using namespace std;

class Trie {
public:
  virtual ~Trie() {}

  virtual bool get_ith(const read_t& read, size_t i, string& r_word, read_t& r_read,
                       bool ignore_empty = false) const = 0;
  virtual void insert(const read_t& read, const string& str, unsigned n) = 0;
  virtual size_t count_total(const read_t& read, bool ignore_empty = false) const = 0;

  virtual void load(InSerializer&) = 0;
  virtual void save(OutSerializer&) const = 0;

  virtual void write(DumpStream& out) const = 0;

  bool sample(const read_t& label, string& r_word, read_t& r_read,
              bool ignore_empty = false) const;

};

/*
ostream& operator << (ostream& out, const Trie* t) {
  write_pointer<Trie>(out, t);
  return out;
}

ostream& operator << (ostream& out, const Trie& t) {
  t.write(out);
  return out;
}
*/
}
