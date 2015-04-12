#include <gtest/gtest.h>

#include "array_trie_builder.hpp"
#include "trie.hpp"

namespace ppg {

TEST(ArrayTrieBuilder, trivial) {
  ArrayTrieBuilder b;
  read_t read;
  read.push_back(1);
  b.add(read, 1, 1);
  b.add(read, 2, 1);
  b.add(read, 1, 1);

  pfi::lang::shared_ptr<Trie> t = b.build();

  ASSERT_EQ(3u, t->count_total(read, false));
  id_t w;
  read_t r;
  t->get_ith(read, 0, w, r, false);
  ASSERT_EQ(1u, w);
  t->get_ith(read, 1, w, r, false);
  ASSERT_EQ(1u, w);
  t->get_ith(read, 2, w, r, false);
  ASSERT_EQ(2u, w);
}

}  // namespace ppg
