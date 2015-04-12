#include "model.hpp"

#include <string>
#include <utility>
#include <vector>

#include "dictionary.hpp"
#include "fwd.hpp"
#include "ngram.hpp"
#include "util.hpp"
#include "random.hpp"
#include "sentence.hpp"

using std::pair;
using std::string;
using std::vector;

namespace ppg {
namespace  {

bool is_parindrome(const read_t& read, int l, int r) {
  for (int il = l, ir = r; il < ir; ++il, --ir) {
    if (read[il] != read[ir]) {
      return false;
    }
  }
  return true;
}

void make_right_candidates(
    const read_t& center_read,
    vector<pair<State, read_t> >& cands) {
  int len = static_cast<int>(center_read.size());
  for (int i = 1; i <= len - 1; ++i) {
    // 0, 1, .., i-1 [i, .., len-1]
    if (!is_parindrome(center_read, i, len - 1)) {
      continue;
    }
    read_t rst;
    for (int j = i - 1; j >= 0; --j) {
      rst.push_back(center_read[j]);
    }
    cands.push_back(make_pair(RIGHT, rst));
  }
}

void make_left_candidates(
    const read_t& center_read,
    vector<pair<State, read_t> >& cands) {
  int len = static_cast<int>(center_read.size());
  for (int i = 0; i < len - 1; ++i) {
    // [0, 1, .., i], i+1, .., len-1
    if (!is_parindrome(center_read, 0, i)) {
      continue;
    }

    read_t rst;
    for (int j = i + 1; j < len; ++j) {
      rst.push_back(center_read[j]);
    }
    cands.push_back(make_pair(LEFT, rst));
  }
}

void make_sentence(
    const std::vector<Word>& left,
    const std::vector<Word>& right,
    Sentence& sentence) {
  std::vector<Word> ws(left.rbegin(), left.rend());
  if (!right.empty()) {
    ws.insert(ws.end(), right.begin() + 1, right.end());
  }
  ws.swap(sentence.words);
}

}  // namespace

bool Model::sample_next(
    bool go_right,
    SearchState& state,
    bool ignore_eos) const {
  const vector<Word>& h = go_right ? state.right : state.left;
  const string& history = h[h.size() - 1].str;
  id_t history_id = dictionary.id_of_string(history);
  // LOG() << "kaibun::sample_next:  history: " << history << " read: " << read;

  const unsigned len = state.read.size();
  const Ngram& ngram = go_right ? forward : backward;

  id_t r;
  read_t r_read;
  if (!ngram.sample(history_id, state.read, r, r_read, ignore_eos)) {
    return false;
  }

  const unsigned res_len = r_read.size();
  if (len == res_len) {
    state.state = BALANCE;
    state.read.clear();
  } else if (len < res_len) {
    state.state = go_right ? LEFT : RIGHT;
    read_t(r_read.begin() + len, r_read.end()).swap(state.read);
  } else {
    state.state = go_right ? RIGHT : LEFT;
    state.read.erase(state.read.begin(), state.read.begin() + res_len);
  }

  std::string rword = dictionary.string_of_id(r);
  if (go_right) {
    state.right.push_back(Word(rword, r_read));
  } else {
    read_t rev(r_read.rbegin(), r_read.rend());
    state.left.push_back(Word(rword, rev));
  }

  return true;
}

bool Model::sample_center(SearchState& state) const {
  id_t center_id;
  read_t center_read;

  if (!unigram.sample(center_id, center_read)) {
    return false;
  }

  vector<pair<State, read_t> > cands;
  if (is_parindrome(center_read, 0, center_read.size() - 1)) {
    cands.push_back(make_pair(BALANCE, read_t()));
  }
  make_right_candidates(center_read, cands);
  make_left_candidates(center_read, cands);

  if (cands.empty()) {
    return false;
  }

  std::string center = dictionary.string_of_id(center_id);
  unsigned id = random_int(cands.size());
  state.state = cands[id].first;
  state.read = cands[id].second;
  state.right.push_back(Word(center, center_read));
  state.left.push_back(Word(center, center_read));

  return true;
}

bool Model::try_make(Sentence& ret) const {
  SearchState state;

  if (!sample_center(state)) {
    return false;
  }

  // LOG() << "center: " << center << " " << state << " " << center_read;

  int depth = 0;
  while (true) {
    depth++;
    if (depth == 30)
      return false;
    // LOG(DEBUG, state << ' ' << read_to_str(read));
    switch (state.state) {
      case BALANCE: {
        if (!sample_next(true, state, depth < 10)) {
          return false;
        }
        if (state.state == BALANCE) {
          if (!sample_next(false, state, depth < 10)) {
            return false;
          }
          if (state.state == BALANCE) {
            make_sentence(state.left, state.right, ret);
            return true;
          } else {
            // eos was not sampled
            return false;
          }
        }
      }
        break;

      case RIGHT: case LEFT: {
        /*
          unsigned r = randomInt(depth + 3);
          if (r == 0)
          return false;
        */
        if (!sample_next(state.state == RIGHT, state, true)) {
          return false;
        }

        if ((state.state == RIGHT && state.right.back().read.empty()) ||
            (state.state == LEFT && state.left.back().read.empty())) {
          // eos was sampled
          return false;
        }
      }
        break;
    }
  }
}

void Model::swap_dictionary(Dictionary& dictionary) {
  Model::dictionary = dictionary;
}

void Model::swap_unigram(Unigram& unigram) {
  Model::unigram.swap(unigram);
}

void Model::swap_forward(Ngram& forward) {
  Model::forward.swap(forward);
}
void Model::swap_backward(Ngram& backward) {
  Model::backward.swap(backward);
}

}  // namespace ppg
