#pragma once

#include "fwd.hpp"
#include <string>
#include <map>

namespace ppg {

class Model;
class Sentence;

class ModelBuilder {
 public:

  void procSentence(const Sentence& sentence);

  void appendUnigram(const std::string& word, const read_t& read);

  void appendForward(const std::string& history,
                     const std::string& word,
                     const read_t& read);

  void appendBackward(const std::string& history,
                      const std::string& word,
                      const read_t& read);

  void swap(Model& model);

 private:
  std::map<std::pair<read_t, std::string>, unsigned> unigram_map;
  std::map<std::string, std::map<std::pair<read_t, std::string>, unsigned> > forward_map;
  std::map<std::string, std::map<std::pair<read_t, std::string>, unsigned> > backward_map;

};


}
