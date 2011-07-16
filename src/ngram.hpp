#pragma once

#include "fwd.hpp"
#include <string>
#include "hashmap.hpp"
#include "trie.hpp"
#include "hashtrie.hpp"
#include "arraytrie.hpp"
#include "dictionary.hpp"

namespace kaibun {

using namespace std;

class Ngram {
public:
  ~Ngram();
  typedef hashmap<int, Trie*> table_t;
  static string none;

  void insert(const string& history, const string& w, const read_t& r, unsigned count = 1);
  
  bool sample(const string& str, const read_t& label,
              string& r_word, read_t& r_read, bool ignore_eos) const;

  void save(OutSerializer&) const;
  void load(InSerializer&);

  void write(DumpStream& out) const;
private:
  table_t table;
};

inline
InSerializer& operator >> (InSerializer& s, Trie*& t) {
  bool non_null;
  s >> non_null;
  if (non_null) {
    //t = new HashTrie();
    t = new ArrayTrie();
    s >> *t;
  }
  return s;
}

}
