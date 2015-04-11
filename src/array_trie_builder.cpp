#include "ArrayTrieBuilder.hpp"
#include <algorithm>
#include "arraytrie.hpp"

namespace ppg {

using namespace std;

ArrayTrie ArrayTrieBuilder::build() const {
  sort(data.begin(), data.end());

  vector<ArrayTrie::Node> nodes;
  for (size_t i = 0; i < data.size(); ++i) {
    
  }
}

}
