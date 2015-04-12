#ifndef UNIGRAM_HPP_82B7E0C2_D813_479B_984C_8CBCA98BE973_
#define UNIGRAM_HPP_82B7E0C2_D813_479B_984C_8CBCA98BE973_

#include <algorithm>

#include <pficommon/data/serialization.h>

#include "fwd.hpp"
#include "trie.hpp"
#include "trie_serialization.hpp"

namespace ppg {

class Unigram {
 public:
  Unigram();

  void insert(id_t w, const read_t& r, unsigned count = 1);

  bool sample(id_t& w, read_t& r) const;

  void swap(Unigram& unigram);

 private:
  friend class pfi::data::serialization::access;

  template <class Ar>
  void serialize(Ar& ar) {
    ar & MEMBER(trie);
  }

  pfi::lang::shared_ptr<Trie> trie;
};

}  // namespace ppg

#endif  // UNIGRAM_HPP_82B7E0C2_D813_479B_984C_8CBCA98BE973_
