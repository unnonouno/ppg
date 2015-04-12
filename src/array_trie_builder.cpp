#include "array_trie_builder.hpp"

#include <algorithm>
#include <utility>
#include <vector>

#include "array_trie.hpp"

namespace ppg {

void ArrayTrieBuilder::add(const read_t& read, id_t str, unsigned count) {
  data.push_back(Entry());
  data.back().read = read;
  data.back().str = str;
  data.back().count = count;
}

pfi::lang::shared_ptr<Trie> ArrayTrieBuilder::build() {
  std::sort(data.begin(), data.end());

  std::vector<ArrayTrie::Node> nodes;
  unsigned count = 0;
  for (size_t i = 0; i < data.size(); ++i) {
    count += data[i].count;
    if (i + 1 == data.size()
        || data[i].read != data[i + 1].read
        || data[i].str != data[i + 1].str) {
      nodes.push_back(ArrayTrie::Node());
      nodes.back().read = data[i].read;
      nodes.back().str = data[i].str;
      nodes.back().count = count;  // accumulate count
    }
  }

  pfi::lang::shared_ptr<ArrayTrie> t(new ArrayTrie());
  t->data.swap(nodes);
  return t;
}

}  // namespace ppg
