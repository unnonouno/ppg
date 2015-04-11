#pragma once

#include <string>
#include <vector>
#include "fwd.hpp"

namespace ppg {

class ArrayTrie;
struct ArrayTrie::Node;

class ArrayTrieBuilder {
 public:
  void add(const read_t& read,
           const std::string& str) {
    data.push_back(Node(read, str, 1));
  }

  ArrayTrie build() const;

 private:
  mutable std::vector<ArrayTrie::Node> data;
};

}
