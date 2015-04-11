#include "model_builder.hpp"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "dictionary.hpp"
#include "model.hpp"
#include "unigram.hpp"
#include "ngram.hpp"
#include "sentence.hpp"

using std::vector;

namespace ppg {

void ModelBuilder::proc_sentence(const Sentence& sentence) {
  const vector<Word>& ws = sentence.words;
  if (ws.empty())
    return;

  for (size_t i = 0; i < ws.size(); ++i) {
    const Word& word = ws[i];
    if (!word.read.empty()) {
      append_unigram(word.str, word.read);

      if (i != 0) {
        append_forward(ws[i - 1].str, word.str, word.read);
      }

      read_t rev(word.read);
      reverse(rev.begin(), rev.end());
      if (i != ws.size() - 1) {
        append_backward(ws[i + 1].str, word.str, rev);
      }
    }
  }

  append_forward(ws[ws.size() - 1].str, "", read_t());
  append_backward(ws[0].str, "", read_t());
}

void ModelBuilder::append_unigram(
    const std::string& word,
    const read_t& read) {
  id_t word_id = dictionary.id_of_string(word);
  unigram_map[make_pair(read, word_id)] += 1;
}

void ModelBuilder::append_forward(
    const std::string& history,
    const std::string& word,
    const read_t& read) {
  id_t history_id = dictionary.id_of_string(history);
  id_t word_id = dictionary.id_of_string(word);
  forward_map[history_id][make_pair(read, word_id)] += 1;
}

void ModelBuilder::append_backward(
    const std::string& history,
    const std::string& word,
    const read_t& read) {
  id_t history_id = dictionary.id_of_string(history);
  id_t word_id = dictionary.id_of_string(word);
  backward_map[history_id][make_pair(read, word_id)] += 1;
}

void ModelBuilder::swap(Model& model) {
  Unigram unigram;
  FOREACH(it, unigram_map) {
    unigram.insert(it->first.second,
                   it->first.first,
                   it->second);
  }

  Ngram forward;
  FOREACH(it, forward_map) {
    FOREACH(it2, it->second) {
      // if (it2->second >= 4)
      forward.insert(it->first,
                     it2->first.second,
                     it2->first.first,
                     it2->second);
    }
  }
  Ngram backward;
  FOREACH(it, backward_map) {
    FOREACH(it2, it->second) {
      // if (it2->second >= 4)
      backward.insert(it->first,
                      it2->first.second,
                      it2->first.first,
                      it2->second);
    }
  }

  // return Model(forward, backward, unigram);
  model.swap_dictionary(dictionary);
  model.swap_unigram(unigram);
  model.swap_forward(forward);
  model.swap_backward(backward);
}

}  // namespace ppg
