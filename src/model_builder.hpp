#ifndef MODEL_BUILDER_HPP_4F6E0BFA_4905_413E_8ED2_0E8ACFD87B60_
#define MODEL_BUILDER_HPP_4F6E0BFA_4905_413E_8ED2_0E8ACFD87B60_

#include <algorithm>
#include <map>
#include <string>
#include <utility>

#include "fwd.hpp"
#include "dictionary.hpp"

namespace ppg {

class Model;
struct Sentence;

class ModelBuilder {
 public:
  void proc_sentence(const Sentence& sentence);

  void append_unigram(const std::string& word, const read_t& read);

  void append_forward(
      const std::string& history,
      const std::string& word,
      const read_t& read);

  void append_backward(
      const std::string& history,
      const std::string& word,
      const read_t& read);

  void swap(Model& model);

 private:
  typedef std::map<std::pair<read_t, id_t>, unsigned> UnigramMap;
  typedef std::map<id_t, UnigramMap> BigramMap;

  Dictionary dictionary;
  UnigramMap unigram_map;
  BigramMap forward_map;
  BigramMap backward_map;
};

}  // namespace ppg

#endif  // MODEL_BUILDER_HPP_4F6E0BFA_4905_413E_8ED2_0E8ACFD87B60_
