#pragma once

#include "fwd.hpp"
#include <string>

namespace ppg {

class Trie {
public:
  virtual ~Trie() {}

  virtual bool get_ith(const read_t& read,
                       size_t i,
                       std::string& r_word,
                       read_t& r_read,
                       bool ignore_empty = false) const = 0;

  virtual void insert(const read_t& read, 
                      const std::string& str,
                      unsigned n) = 0;
  
  virtual size_t count_total(const read_t& read,
                             bool ignore_empty = false) const = 0;

  bool sample(const read_t& label,
              std::string& r_word,
              read_t& r_read,
              bool ignore_empty = false) const;

};

}