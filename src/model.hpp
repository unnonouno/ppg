#ifndef MODEL_HPP_149C8476_F8CB_4A2D_9595_68423FC64A5B_
#define MODEL_HPP_149C8476_F8CB_4A2D_9595_68423FC64A5B_

#include <string>
#include <vector>

#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/serialization.h>
#include <pficommon/math/random.h>

#include "dictionary.hpp"
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
  void swap_dictionary(Dictionary& dictionary);
  void swap_unigram(Unigram& unigram);
  void swap_forward(Ngram& forward);
  void swap_backward(Ngram& backward);

  bool try_make(Sentence& sentence) const;

 private:
  struct SearchState {
    read_t read;
    std::vector<Word> right;
    std::vector<Word> left;
    State state;
  };

  friend class pfi::data::serialization::access;

  template <class Ar>
  void serialize(Ar& ar) {
    ar
        & MEMBER(dictionary)
        & MEMBER(forward)
        & MEMBER(backward)
        & MEMBER(unigram);
  }

  bool sample_next(
      bool go_right,
      SearchState& state,
      bool ignore_eos) const;

  bool sample_center(SearchState& state) const;

  Dictionary dictionary;
  Ngram forward;
  Ngram backward;
  Unigram unigram;
};

}  // namespace ppg

#endif  // MODEL_HPP_149C8476_F8CB_4A2D_9595_68423FC64A5B_
