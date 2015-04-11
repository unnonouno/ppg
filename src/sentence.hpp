#pragma once

#include "fwd.hpp"

namespace ppg {

struct Word {
  std::string str;
  read_t read;

  Word(const std::string& s, const read_t& r)
      : str(s), read(r) {}
};

struct Sentence {
  std::vector<Word> words;
};

}
