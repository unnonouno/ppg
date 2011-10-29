#pragma once

#include "fwd.hpp"
#include <string>
#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/serialization.h>
#include <pficommon/data/unordered_map.h>
#include "TrieSerialization.hpp"

namespace ppg {

class Ngram {
 public:
  static std::string none;
  
  void insert(const std::string& history,
              const std::string& word,
              const read_t& read,
              unsigned count = 1);
  
  bool sample(const std::string& str,
              const read_t& label,
              std::string& r_word,
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

}
