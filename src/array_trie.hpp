#ifndef ARRAY_TRIE_HPP_406F0A9E_83CA_4242_B87F_DD7ACCB0E46C_
#define ARRAY_TRIE_HPP_406F0A9E_83CA_4242_B87F_DD7ACCB0E46C_

#include <ostream>
#include <utility>
#include <vector>

#include <pficommon/data/serialization.h>

#include "fwd.hpp"
#include "trie.hpp"

namespace ppg {

class ArrayTrie : public Trie {
 public:
  bool get_ith(
      const read_t& read,
      size_t i,
      id_t& r_word,
      read_t& r_read,
      bool ignore_empty = false) const;

  void insert(
      const read_t& read,
      id_t str,
      unsigned n);

  void print(std::ostream& out) const;

  size_t count_total(
      const read_t& read,
      bool ignore_empty = false) const;

 private:
  struct Node {
    read_t read;
    id_t str;
    unsigned count;

    friend class pfi::data::serialization::access;
    template <class Ar>
    void serialize(Ar& ar) {
      ar & MEMBER(read) & MEMBER(str) & MEMBER(count);
    }
  };

  friend class pfi::data::serialization::access;
  template <class Ar>
  void serialize(Ar& ar) {
    ar & MEMBER(data);
  }

  std::pair<size_t, size_t> get_range(const read_t& read) const;

  size_t get_begin(const read_t& read, id_t str) const;
  size_t get_begin(const read_t& read) const;

  unsigned get_count(size_t pos) const;

  unsigned get_offset(size_t index) const;

  std::vector<Node> data;
};

}  // namespace ppg

#endif  // ARRAY_TRIE_HPP_406F0A9E_83CA_4242_B87F_DD7ACCB0E46C_
