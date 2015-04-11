#ifndef ARRAY_TRIE_BUILDER_HPP_64E2C8CA_2482_43FB_B7D6_F389B94D8D2F_
#define ARRAY_TRIE_BUILDER_HPP_64E2C8CA_2482_43FB_B7D6_F389B94D8D2F_

#include <string>
#include <vector>

#include "array_trie.hpp"
#include "fwd.hpp"

namespace ppg {

class ArrayTrieBuilder {
 public:
  void add(const read_t& read,
           const std::string& str) {
    data.push_back(ArrayTrie::Node(read, str, 1));
  }

  ArrayTrie build() const;

 private:
  mutable std::vector<ArrayTrie::Node> data;
};

}  // namespace ppg

#endif  // ARRAY_TRIE_BUILDER_HPP_64E2C8CA_2482_43FB_B7D6_F389B94D8D2F_
