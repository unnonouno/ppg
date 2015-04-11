#pragma once

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
