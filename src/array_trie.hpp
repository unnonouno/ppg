#ifndef ARRAY_TRIE_HPP_406F0A9E_83CA_4242_B87F_DD7ACCB0E46C_
#define ARRAY_TRIE_HPP_406F0A9E_83CA_4242_B87F_DD7ACCB0E46C_

#include <ostream>
#include <string>
#include <vector>

#include <pficommon/data/serialization.h>

#include "fwd.hpp"
#include "trie.hpp"

namespace ppg {

class ArrayTrie : public Trie {
public:
  virtual ~ArrayTrie() {}

  bool get_ith(const read_t& read,
               size_t i,
               std::string& r_word,
               read_t& r_read,
               bool ignore_empty = false) const;

  void insert(const read_t& read,
              const std::string& str,
              unsigned n);

  void print(std::ostream& out) const;

  size_t count_total(const read_t& read,
                     bool ignore_empty = false) const;

  struct Node {
    read_t read;
    std::string str;
    unsigned count;

    friend class pfi::data::serialization::access;
    template <class A>
    void serialize(A &a) {
      a & read & str & count;
    }
  };

private:
  friend class pfi::data::serialization::access;
  template <class A>
  void serialize(A &a) {
    a & data;
  }

  std::pair<size_t, size_t> get_range(const read_t& read) const;

  size_t get_begin(const read_t& read) const;

  unsigned get_count(size_t pos) const;

  unsigned get_offset(size_t index) const;

  std::vector<Node> data;
};

}

#endif  // ARRAY_TRIE_HPP_406F0A9E_83CA_4242_B87F_DD7ACCB0E46C_
