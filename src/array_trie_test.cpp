#include <algorithm>
#include <iostream>

#include <gtest/gtest.h>

#include "array_trie.hpp"
#include "util.hpp"

using std::cout;

namespace ppg {

bool operator ==(const read_t& r1, const read_t& r2) {
  if (r1.size() != r2.size())
    return false;
  return equal(r1.begin(), r1.end(), r2.begin());
}

TEST(array_trie, trivial) {
  ArrayTrie t;
  read_t a = str_to_read("A");
  read_t ab = str_to_read("AB");
  read_t abc = str_to_read("ABC");
  read_t abd = str_to_read("ABD");
  id_t i_a = 0;
  id_t i_abc = 2;
  id_t i_abd = 3;

  t.insert(abc, i_abc, 1);
  t.print(cout);

  read_t r;
  id_t w;
  t.get_ith(abc, 0, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);

  t.insert(abc, i_abc, 1);

  t.get_ith(ab, 0, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);
  t.get_ith(ab, 1, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);

  t.insert(abd, i_abd, 1);
  t.get_ith(ab, 0, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);
  t.get_ith(ab, 1, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);
  EXPECT_TRUE(t.get_ith(ab, 2, w, r));
  EXPECT_EQ(i_abd, w);
  EXPECT_EQ(abd, r);
  t.print(cout);
  EXPECT_EQ(3u, t.count_total(ab));
  EXPECT_EQ(3u, t.count_total(a));
  EXPECT_EQ(1u, t.count_total(abd));


  t.insert(a, i_a, 1);
  t.print(cout);
  t.get_ith(a, 0, w, r);
  EXPECT_EQ(i_a, w);
  EXPECT_EQ(a, r);

  t.get_ith(a, 1, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);

  t.get_ith(a, 2, w, r);
  EXPECT_EQ(i_abc, w);
  EXPECT_EQ(abc, r);

  t.get_ith(a, 3, w, r);
  EXPECT_EQ(i_abd, w);
  EXPECT_EQ(abd, r);
}

}  // namespace ppg
