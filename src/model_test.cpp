#include <iostream>

#include <gtest/gtest.h>

#include "kaibun.hpp"
#include "ngram.hpp"
#include "unigram.hpp"
#include "util.hpp"
#include "sentence.hpp"

namespace ppg {

TEST(trie, trivial) {
  Ngram forward;
  Ngram backward;
  Unigram unigram;

  unigram.insert("A", str_to_read("A"), 1);
  // unigram.insert(str_to_read("ABC"), "ABC", 1);
  forward.insert("A", "BA", str_to_read("BA"));
  forward.insert("BA", "", str_to_read(""));
  // forward.insert("GO", "HBA", str_to_read("HBA"));
  // forward.insert("HBA", "", str_to_read(""));
  // backward.insert("HOGE", "AB", str_to_read("AB"));
  backward.insert("A", "ABAB", str_to_read("BABA"));
  backward.insert("ABAB", "", str_to_read(""));

  Model model;
  model.swap_unigram(unigram);
  model.swap_forward(forward);
  model.swap_backward(backward);

  Sentence s;
  model.try_make(s);
  std::cout << "--" << std::endl;
  FOREACH(i, s.words) {
    std::cout << i->str << std::endl;
  }
  std::cout << "--" << std::endl;
}

}  // namespace ppg
