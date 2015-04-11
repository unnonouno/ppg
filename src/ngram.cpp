#include "ngram.hpp"

#include <algorithm>

#include "array_trie.hpp"
#include "hash_trie.hpp"
#include "trie.hpp"
#include "util.hpp"

using pfi::lang::shared_ptr;

namespace ppg {

bool Ngram::sample(
    id_t str,
    const read_t& label,
    id_t& r_word,
    read_t& r_read,
    bool ignore_eos) const {
  table_t::const_iterator p = table.find(str);
  if (p == table.end()) {
    return false;
  }

  return p->second->sample(label, r_word, r_read, ignore_eos);
}

void Ngram::insert(
    id_t history,
    id_t w,
    const read_t& r,
    unsigned count) {
  if (!table[history]) {
    // table[id] = new HashTrie();
    table[history] = shared_ptr<Trie>(new ArrayTrie());
  }
  table[history]->insert(r, w, count);
}

void Ngram::swap(Ngram& ngram) {
  table.swap(ngram.table);
}

}  // namespace ppg
