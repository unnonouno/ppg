#pragma once

#include "fwd.hpp"
#include <string>
#include <map>

namespace ppg {

class Model;
class Sentence;

class ModelBuilder {
 public:

  void proc_sentence(const Sentence& sentence);

  void append_unigram(const std::string& word, const read_t& read);

  void append_forward(const std::string& history,
                      const std::string& word,
                      const read_t& read);

  void append_backward(const std::string& history,
                       const std::string& word,
                       const read_t& read);

  void swap(Model& model);

 private:
  std::map<std::pair<read_t, std::string>, unsigned> unigram_map;
  std::map<std::string, std::map<std::pair<read_t, std::string>, unsigned> > forward_map;
  std::map<std::string, std::map<std::pair<read_t, std::string>, unsigned> > backward_map;

};


}
