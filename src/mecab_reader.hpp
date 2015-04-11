#ifndef MECAB_READER_HPP_0CA94B61_5835_4425_9F64_06A3850E1AF6_
#define MECAB_READER_HPP_0CA94B61_5835_4425_9F64_06A3850E1AF6_

#include <istream>

#include "read_manager.hpp"

namespace ppg {

class Sentence;

class MecabReader {
 public:
  MecabReader(std::istream& in, ReadManager& read_manager);

  bool get_sentence(Sentence& sentence);
  
 private:
  std::istream& input;
  ReadManager& read_manager;
};

}

#endif  // MECAB_READER_HPP_0CA94B61_5835_4425_9F64_06A3850E1AF6_
