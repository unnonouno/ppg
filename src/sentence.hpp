#ifndef SENTENCE_HPP_C57B0EFE_06EC_4160_9DBA_14C95DEA5B73_
#define SENTENCE_HPP_C57B0EFE_06EC_4160_9DBA_14C95DEA5B73_

#include <string>
#include <vector>

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

}  // namespace ppg

#endif  // SENTENCE_HPP_C57B0EFE_06EC_4160_9DBA_14C95DEA5B73_
