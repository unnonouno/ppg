#include "trie.hpp"

#include "random.hpp"

namespace ppg {

bool Trie::sample(
    const read_t& label,
    id_t& r_word,
    read_t& r_read,
    bool ignore_empty) const {
  const size_t total = count_total(label, ignore_empty);
  // LOG() << "total: " << total;
  if (total == 0) {
    // LOG() << "Trie::sample  not found";
    return false;
  }

  const size_t id = random_int(total);
  return get_ith(label, id, r_word, r_read, ignore_empty);
}

}  // namespace ppg
