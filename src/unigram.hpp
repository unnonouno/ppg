#pragma once

#include "fwd.hpp"
#include <string>

#include <pficommon/data/serialization.h>
#include "TrieSerialization.hpp"
#include "Trie.hpp"

namespace ppg {

class Unigram {
 public:
  Unigram();

  void insert(const std::string& w, const read_t& r, unsigned count = 1);

  bool sample(std::string& w, read_t& r) const;

  void swap(Unigram& unigram);

 private:
  friend class pfi::data::serialization::access;

  template <class A>
  void serialize(A &a) {
    a & trie;
  }

  pfi::lang::shared_ptr<Trie> trie;
};

}
