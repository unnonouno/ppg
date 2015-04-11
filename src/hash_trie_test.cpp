#include <iostream>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "hash_trie.hpp"
#include "util.hpp"

using std::string;

namespace ppg {

TEST(hash_trie, trivial) {
  HashTrie t;
  read_t abc = str_to_read("ABC");
  read_t ab = str_to_read("AB");
  read_t a = str_to_read("A");
  read_t abd = str_to_read("ABD");

  t.insert(abc, "ABC", 1);
  // [abc]
  t.print(cout);

  read_t r;
  string w;
  t.get_ith(abc, 0, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);

  t.insert(abc, "ABC", 1);
  // [abc, abc]
  t.get_ith(ab, 0, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);
  t.get_ith(ab, 1, w, r);
  EXPECT_EQ("ABC", w);
  EXPECT_EQ(abc, r);

  t.insert(abd, "ABD", 1);
  // [abc, abc, abd]
  // Order for C and D is not defined
  read_t r1, r2, r3;
  string w1, w2, w3;
  t.get_ith(ab, 0, w1, r1);
  t.get_ith(ab, 1, w2, r2);
  t.get_ith(ab, 2, w3, r3);
  EXPECT_TRUE(
      (w1 == "ABC" && w2 == "ABC" && w3 == "ABD" &&
       r1 == abc && r2 == abc && r3 == abd) ||
      (w1 == "ABD" && w2 == "ABC" && w3 == "ABC" &&
       r1 == abd && r2 == abc && r3 == abc));

  t.print(cout);
  EXPECT_EQ(3u, t.count_total(ab));
  EXPECT_EQ(3u, t.count_total(a));
  EXPECT_EQ(1u, t.count_total(abd));


  t.insert(a, "A", 1);
  // [a, abc, abc, abd]
  t.print(cout);
  t.get_ith(a, 0, w, r);
  EXPECT_EQ("A", w);
  EXPECT_EQ(a, r);

  t.get_ith(a, 1, w1, r1);
  t.get_ith(a, 2, w2, r2);
  t.get_ith(a, 3, w3, r3);

  EXPECT_TRUE(
      (w1 == "ABC" && w2 == "ABC" && w3 == "ABD" &&
       r1 == abc && r2 == abc && r3 == abd) ||
      (w1 == "ABD" && w2 == "ABC" && w3 == "ABC" &&
       r1 == abd && r2 == abc && r3 == abc));
}

}  // namespace ppg
