#ifndef TRIE_BUILDER_HPP_5B05EC75_78D6_4241_B211_19DAE7A0A324_
#define TRIE_BUILDER_HPP_5B05EC75_78D6_4241_B211_19DAE7A0A324_

#include <pficommon/lang/shared_ptr.h>

#include "trie.hpp"

namespace ppg {

class TrieBuilder {
 public:
  virtual ~TrieBuilder() {}

  virtual void add(const read_t& read, id_t str, unsigned count) = 0;

  virtual pfi::lang::shared_ptr<Trie> build() = 0;
};

}  // namespace ppg

#endif  // TRIE_BUILDER_HPP_5B05EC75_78D6_4241_B211_19DAE7A0A324_
