#include "unigram.hpp"

#include <algorithm>
#include <string>

#include "trie.hpp"

namespace ppg {

Unigram::Unigram() : trie(new ArrayTrie()) {}

void Unigram::insert(const std::string& w, const read_t& r, unsigned count) {
  trie->insert(r, w, count);
}

bool Unigram::sample(std::string& word, read_t&read) const {
  return trie->sample(read_t(), word, read);
}

void Unigram::swap(Unigram& unigram) {
  std::swap(trie, unigram.trie);
}

}  // namespace ppg
