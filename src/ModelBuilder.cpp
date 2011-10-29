#include "ModelBuilder.hpp"
#include "Kaibun.hpp"
#include "Unigram.hpp"
#include "Ngram.hpp"
#include "Sentence.hpp"

namespace ppg {

using namespace std;

void ModelBuilder::procSentence(const Sentence& sentence) {
  const vector<Word>& ws = sentence.words;
  if (ws.empty())
    return;

  for (size_t i = 0; i < ws.size(); ++i) {
    const Word& word = ws[i];
    if (!word.read.empty()) {
      appendUnigram(word.str, word.read);
    
      if (i != 0) {
        appendForward(ws[i - 1].str, word.str, word.read);
      }

      read_t rev(word.read);
      reverse(rev.begin(), rev.end());
      if (i != ws.size() - 1) {
        appendBackward(ws[i + 1].str, word.str, rev);
      }
    }
  }

  appendForward(ws[ws.size() - 1].str, "", read_t());
  appendBackward(ws[0].str, "", read_t());
}

void ModelBuilder::appendUnigram(const std::string& word, const read_t& read) {
  unigram_map[make_pair(read, word)] += 1;
}

void ModelBuilder::appendForward(const std::string& history,
                                 const std::string& word,
                                 const read_t& read) {
  forward_map[history][make_pair(read, word)] += 1;
}

void ModelBuilder::appendBackward(const std::string& history,
                                  const std::string& word,
                                  const read_t& read) {
  backward_map[history][make_pair(read, word)] += 1;
}

void ModelBuilder::swap(Model& model) {
  Unigram unigram;
  FOREACH (it, unigram_map) {
    unigram.insert(it->first.second, it->first.first, it->second);
  }

  Ngram forward;
  FOREACH (it, forward_map) {
    FOREACH (it2, it->second) {
      //if (it2->second >= 4)
        forward.insert(it->first, it2->first.second, it2->first.first, it2->second);
    }
  }
  Ngram backward;
  FOREACH (it, backward_map) {
    FOREACH (it2, it->second) {
      //      if (it2->second >= 4)
        backward.insert(it->first, it2->first.second, it2->first.first, it2->second);
    }
  }

  //return Model(forward, backward, unigram);
  model.swapUnigram(unigram);
  model.swapForward(forward);
  model.swapBackward(backward);
}

}
