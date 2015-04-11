#include <gtest/gtest.h>
#include <iostream>
#include "Kaibun.hpp"
#include "Ngram.hpp"
#include "Unigram.hpp"
#include "Util.hpp"
#include "Sentence.hpp"

namespace ppg {

using namespace std;

TEST(trie, trivial) {
  Ngram forward;
  Ngram backward;
  Unigram unigram;

  unigram.insert("A", str_to_read("A"), 1);
  //unigram.insert(str_to_read("ABC"), "ABC", 1);
  forward.insert("A", "BA", str_to_read("BA"));
  forward.insert("BA", "", str_to_read(""));
  //forward.insert("GO", "HBA", str_to_read("HBA"));
  //forward.insert("HBA", "", str_to_read(""));
  //backward.insert("HOGE", "AB", str_to_read("AB"));
  backward.insert("A", "ABAB", str_to_read("BABA"));
  backward.insert("ABAB", "", str_to_read(""));

  Model model;
  model.swap_unigram(unigram);
  model.swap_forward(forward);
  model.swap_backward(backward);

  Sentence s;
  model.try_make(s);
  cout << "--" << endl;
  FOREACH (i, s.words) {
    cout << i->str << endl;
  }
  cout << "--" << endl;
}

}
