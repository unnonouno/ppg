#ifndef NGRAM_HPP_99986610_3FCF_4269_A29D_5A3168218D5D_
#define NGRAM_HPP_99986610_3FCF_4269_A29D_5A3168218D5D_

#include <algorithm>

#include <pficommon/data/serialization.h>
#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/unordered_map.h>

#include "fwd.hpp"
#include "trie_serialization.hpp"

namespace ppg {

class Ngram {
 public:
  void insert(
      id_t history,
      id_t word,
      const read_t& read,
      unsigned count = 1);

  bool sample(
      id_t str,
      const read_t& label,
      id_t& r_word,
      read_t& r_read,
      bool ignore_eos) const;

  void swap(Ngram& ngram);

 private:
  friend class pfi::data::serialization::access;
  template <class A>
  void serialize(A &a) {
    a & table;
  }

  typedef pfi::data::unordered_map<int, pfi::lang::shared_ptr<Trie> > table_t;
  table_t table;
};

}  // namespace ppg

#endif  // NGRAM_HPP_99986610_3FCF_4269_A29D_5A3168218D5D_
