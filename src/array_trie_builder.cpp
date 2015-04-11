#include "array_trie_builder.hpp"

#include <algorithm>
#include <vector>

#include "arraytrie.hpp"

namespace ppg {

ArrayTrie ArrayTrieBuilder::build() const {
  std::sort(data.begin(), data.end());

  vector<ArrayTrie::Node> nodes;
  for (size_t i = 0; i < data.size(); ++i) {
  }
}

}  // namespace ppg
