#pragma once

#include "fwd.hpp"
#include <string>
#include <vector>

#include "trie.hpp"

#include "serializer.hpp"

namespace kaibun {

using namespace std;

class ArrayTrie : public Trie {
public:
  virtual ~ArrayTrie() {}

  bool get_ith(const read_t& read, size_t i, string& r_word, read_t& r_read,
               bool ignore_empty = false) const;
  void insert(const read_t& read, const string& str, unsigned n);

  void print(ostream& out) const;

  size_t count_total(const read_t& read, bool ignore_empty = false) const;

  void load(InSerializer&);
  void save(OutSerializer&) const;

  void write(DumpStream& out) const;

  struct Node {
    read_t read;
    string str;
    unsigned count;

    void load(InSerializer&);
    void save(OutSerializer&) const;

    void write(DumpStream&) const;
  };

private:
  pair<unsigned, unsigned> get_range(const read_t& read) const;
  unsigned get_begin(const read_t& read) const;
  unsigned get_count(unsigned pos) const;
  unsigned get_offset(unsigned index) const;

  vector<Node> data;
};

}
