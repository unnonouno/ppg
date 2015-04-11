#include <iostream>

#include <gtest/gtest.h>

#include "hash_trie.hpp"
#include "util.hpp"

using std::cout;

namespace ppg {

TEST(hash_trie, trivial) {
  HashTrie t;
  read_t a = str_to_read("A");
  read_t ab = str_to_read("AB");
  read_t abc = str_to_read("ABC");
  read_t abd = str_to_read("ABD");
  id_t i_a = 0;
  id_t i_abc = 2;
  id_t i_abd = 3;

  t.insert(abc, i_abc, 1);
  // [abc]
  t.print(cout);

  read_t r;
  id_t w;
  t.get_ith(abc, 0, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);

  t.insert(abc, i_abc, 1);
  // [abc, abc]
  t.get_ith(ab, 0, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);
  t.get_ith(ab, 1, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);

  t.insert(abd, i_abd, 1);
  // [abc, abc, abd]
  // Order for C and D is not defined
  read_t r1, r2, r3;
  id_t w1, w2, w3;
  t.get_ith(ab, 0, w1, r1);
  t.get_ith(ab, 1, w2, r2);
  t.get_ith(ab, 2, w3, r3);
  EXPECT_TRUE(
      (w1 == i_abc && w2 == i_abc && w3 == i_abd &&
       r1 == abc && r2 == abc && r3 == abd) ||
      (w1 == i_abd && w2 == i_abc && w3 == i_abc &&
       r1 == abd && r2 == abc && r3 == abc));

  t.print(cout);
  EXPECT_EQ(3u, t.count_total(ab));
  EXPECT_EQ(3u, t.count_total(a));
  EXPECT_EQ(1u, t.count_total(abd));


  t.insert(a, i_a, 1);
  // [a, abc, abc, abd]
  t.print(cout);
  t.get_ith(a, 0, w, r);
  EXPECT_EQ(i_a, w);
  EXPECT_EQ(a, r);

  t.get_ith(a, 1, w1, r1);
  t.get_ith(a, 2, w2, r2);
  t.get_ith(a, 3, w3, r3);

  EXPECT_TRUE(
      (w1 == i_abc && w2 == i_abc && w3 == i_abd &&
       r1 == abc && r2 == abc && r3 == abd) ||
      (w1 == i_abd && w2 == i_abc && w3 == i_abc &&
       r1 == abd && r2 == abc && r3 == abc));
}

}  // namespace ppg
