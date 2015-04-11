#ifndef MODEL_HPP_149C8476_F8CB_4A2D_9595_68423FC64A5B_
#define MODEL_HPP_149C8476_F8CB_4A2D_9595_68423FC64A5B_

#include <string>
#include <vector>

#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/serialization.h>
#include <pficommon/math/random.h>

#include "fwd.hpp"
#include "ngram.hpp"
#include "unigram.hpp"
#include "util.hpp"

namespace ppg {

class Ngram;
struct Word;
struct Sentence;

enum State {
  BALANCE, RIGHT, LEFT
};

class Model {
 public:
  void swap_unigram(Unigram& unigram);
  void swap_forward(Ngram& forward);
  void swap_backward(Ngram& backward);

  bool try_make(Sentence& sentence) const;

 private:
  friend class pfi::data::serialization::access;

  template <class A>
  void serialize(A &a) {
    a & forward & backward & unigram;
  }

  bool sample_next(
      bool go_right,
      read_t& read,
      std::vector<Word>& right,
      std::vector<Word>& left,
      State& state,
      bool ignore_eos) const;

  bool sample_center(
      std::string& r_center,
      read_t& r_read,
      State& state,
      read_t& rest) const;

  Ngram forward;
  Ngram backward;
  Unigram unigram;
};

}  // namespace ppg

#endif  // MODEL_HPP_149C8476_F8CB_4A2D_9595_68423FC64A5B_
