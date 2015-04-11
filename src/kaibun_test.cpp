#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include "kaibun.hpp"
#include "ngram.hpp"
#include "hashtrie.hpp"
#include "util.hpp"

using std::pair;
using std::string;
using std::vector;

namespace ppg {

TEST(trie, trivial) {
  Ngram forward;
  Ngram backward;
  HashTrie unigram;

  vector<pair<string, read_t> > r;
  unigram.insert(str_to_read("HOGE"), "HOGE", 1);
  // unigram.insert(str_to_read("ABC"), "ABC", 1);
  forward.insert("HOGE", "GO", str_to_read("GO"));
  forward.insert("GO", "HBA", str_to_read("HBA"));
  forward.insert("HBA", "", str_to_read(""));
  backward.insert("HOGE", "AB", str_to_read("AB"));
  backward.insert("AB", "", str_to_read(""));
  try_make(forward, backward, unigram, r);
  std::cout << "--" << std::endl;
  FOREACH(i, r) {
    std::cout << i->first << std::endl;
  }
  std::cout << "--" << std::endl;
}

}  // namespace ppg
