#pragma once

#include "fwd.hpp"

#include <string>
#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/serialization.h>
#include <pficommon/math/random.h>
#include "Ngram.hpp"
#include "Unigram.hpp"
#include "Util.hpp"

namespace ppg {

class Ngram;
struct Word;
struct Sentence;

enum State {
  BALANCE, RIGHT, LEFT
};
    

class Model {
public:
  void swapUnigram(Unigram& unigram);
  void swapForward(Ngram& forward);
  void swapBackward(Ngram& backward);

  bool tryMake(Sentence& sentence) const;
private:
  friend class pfi::data::serialization::access;

  template <class A>
  void serialize(A &a) {
    a & forward & backward & unigram;
  }

  bool sampleNext(bool go_right,
                  read_t& read,
                  std::vector<Word>& right,
                  std::vector<Word>& left,
                  State& state,
                  bool ignore_eos
                  ) const;

  bool sampleCenter(std::string& r_center,
                    read_t& r_read,
                    State& state,
                    read_t& rest) const;

  Ngram forward;
  Ngram backward;
  Unigram unigram;
};

}
