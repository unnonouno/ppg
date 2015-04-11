#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "hashtrie.hpp"
#include "util.hpp"

namespace ppg {

using namespace std;

TEST(hash_trie, trivial) {
  HashTrie t;
  read_t abc = str_to_read("ABC");
  read_t ab = str_to_read("AB");
  read_t a = str_to_read("A");
  read_t abd = str_to_read("ABD");

  t.insert(abc, "ABC", 1);
  t.print(cout);

  read_t r;
  string w;
  t.get_ith(abc, 0, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);

  t.insert(abc, "ABC", 1);

  t.get_ith(ab, 0, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);
  t.get_ith(ab, 1, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);

  t.insert(abd, "ABD", 1);
  t.get_ith(ab, 0, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);
  t.get_ith(ab, 1, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);
  t.get_ith(ab, 2, w, r);
  EXPECT_EQ("ABD", w);
  EXPECT_EQ(abd, r);
  t.print(cout);
  EXPECT_EQ(3u, t.count_total(ab));
  EXPECT_EQ(3u, t.count_total(a));
  EXPECT_EQ(1u, t.count_total(abd));


  t.insert(a, "A", 1);
  t.print(cout);
  t.get_ith(a, 0, w, r);
  EXPECT_EQ("A", w);
  EXPECT_EQ(a, r);

  t.get_ith(a, 1, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);

  t.get_ith(a, 2, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);

  t.get_ith(a, 3, w, r);
  EXPECT_EQ("ABD", w);
  EXPECT_EQ(abd, r);
}

}
