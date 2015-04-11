#include "mecab_reader.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "sentence.hpp"

using std::istream;
using std::string;
using std::vector;

namespace ppg {

vector<string> split(const string& s, const string& delim) {
  unsigned pos = 0;
  vector<string> ret;
  while (true) {
    size_t next = s.find_first_of(delim, pos);
    if (next == string::npos) {
      ret.push_back(s.substr(pos));
      break;
    } else {
      ret.push_back(s.substr(pos, next - pos));
      pos = next + delim.size();
    }
  }
  return ret;
}

MecabReader::MecabReader(istream& in, ReadManager& read_manager)
    : input(in), read_manager(read_manager) {
}

bool is_function_word(const string& pos) {
  return pos == "助詞" || pos == "助動詞";
}

bool is_verb(const string& pos) {
  return pos == "動詞";
}

bool MecabReader::get_sentence(Sentence& sentence) {
  sentence.words.clear();
  string word;
  read_t read;
  for (string line; getline(input, line); ) {
    if (line == "EOS") {
      if (!read.empty())
        sentence.words.push_back(Word(word, read));
      return true;
    }
    vector<string> ss = split(line, "\t");
    vector<string> features = split(ss[1], ",");
    string pos = features[0] + ":" + features[1];
    read_t r = read_manager.string_to_read(features[features.size() - 2]);
    if (r.empty() || ss[0] == "…") {
      return true;
    }
    string str = ss[0] + "(" + pos + ")";

    word += str;
    read.insert(read.end(), r.begin(), r.end());

    if (!is_verb(features[0])) {
      sentence.words.push_back(Word(word, read));
      word.clear();
      read.clear();
    }

    // sentence.words.push_back(Word(str, read));
  }
  return false;
}

}  // namespace ppg
