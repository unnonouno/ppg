#include "unigram.hpp"

#include <algorithm>

#include "trie.hpp"

namespace ppg {

Unigram::Unigram() : trie(new ArrayTrie()) {}

void Unigram::insert(id_t w, const read_t& r, unsigned count) {
  trie->insert(r, w, count);
}

bool Unigram::sample(id_t& word, read_t&read) const {
  return trie->sample(read_t(), word, read);
}

void Unigram::swap(Unigram& unigram) {
  std::swap(trie, unigram.trie);
}

}  // namespace ppg
