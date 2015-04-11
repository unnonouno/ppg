#include "Unigram.hpp"
#include "Trie.hpp"

namespace ppg {

using namespace std;
using namespace pfi::lang;

Unigram::Unigram() : trie(new ArrayTrie()) {}

void Unigram::insert(const std::string& w, const read_t& r, unsigned count) {
  trie->insert(r, w, count);
}

bool Unigram::sample(string& word, read_t&read) const {
  return trie->sample(read_t(), word, read);
}

void Unigram::swap(Unigram& unigram) {
  std::swap(trie, unigram.trie);
}

}
