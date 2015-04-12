#ifndef ARRAY_TRIE_BUILDER_HPP_64E2C8CA_2482_43FB_B7D6_F389B94D8D2F_
#define ARRAY_TRIE_BUILDER_HPP_64E2C8CA_2482_43FB_B7D6_F389B94D8D2F_

#include <string>
#include <utility>
#include <vector>

#include <pficommon/lang/shared_ptr.h>

#include "array_trie.hpp"
#include "fwd.hpp"
#include "trie_builder.hpp"

namespace ppg {

class ArrayTrieBuilder : public TrieBuilder {
 public:
  void add(const read_t& read, id_t str, unsigned count);

  pfi::lang::shared_ptr<Trie> build();

 private:
  struct Entry {
    read_t read;
    id_t str;
    unsigned count;

    bool operator <(const Entry& e) const {
      return read < e.read || (read == e.read && str < e.str);
    }
  };

  std::vector<Entry> data;
};

}  // namespace ppg

#endif  // ARRAY_TRIE_BUILDER_HPP_64E2C8CA_2482_43FB_B7D6_F389B94D8D2F_
