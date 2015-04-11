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

static State op[] = { BALANCE, LEFT, RIGHT };

State opposite(State s) {
  return op[s];
}

bool is_parindrome(
    const read_t& read,
    const int l,
    const int r) {
  for (int il = l, ir = r; il < ir; il++, ir--) {
    if (read[il] != read[ir])
      return false;
  }
  return true;
}

bool Model::sample_next(
    bool go_right,
    read_t& read,
    vector<Word>& right,
    vector<Word>& left,
    State& state,
    bool ignore_eos) const {
  const vector<Word>& h = go_right ? right : left;
  const string& history = h[h.size() - 1].str;
  id_t history_id = dictionary.id_of_string(history);
  // LOG() << "kaibun::sample_next:  history: " << history << " read: " << read;

  const unsigned len = read.size();
  const Ngram& ngram = go_right ? forward : backward;

  id_t r;
  read_t r_read;
  if (!ngram.sample(history_id, read, r, r_read, ignore_eos)) {
    return false;
  }
  // LOG() << r << r_read;
  const unsigned res_len = r_read.size();
  if (len == res_len) {
    state = BALANCE;
    read.clear();
  } else if (len < res_len) {
    // state = opposite(state);
    state = go_right ? LEFT : RIGHT;
    read.clear();
    for (unsigned i = len; i < res_len; i++)
      read.push_back(r_read[i]);
  } else {
    state = go_right ? RIGHT : LEFT;
    read.erase(read.begin(), read.begin() + res_len);
  }
  // LOG() << read;

  std::string rword = dictionary.string_of_id(r);
  if (go_right) {
    right.push_back(Word(rword, r_read));
  } else {
    read_t rev(r_read.rbegin(), r_read.rend());
    left.push_back(Word(rword, rev));
  }

  return true;
}

bool Model::sample_center(
    id_t& r_center,
    read_t& r_read,
    State& state,
    read_t& rest) const {
  if (!unigram.sample(r_center, r_read))
    return false;

  const int len = static_cast<int>(r_read.size());
  vector<pair<State, read_t> > cands;

  for (int i = 0; i <= len; i++) {
    if (!is_parindrome(r_read, i, len - 1))
      continue;
    State s = RIGHT;
    read_t rst;
    for (int j = i - 1; j >= 0; j--)
      rst.push_back(r_read[j]);
    if (i == 0)
      s = BALANCE;
    cands.push_back(make_pair(s, rst));
  }

  for (int i = 1; i <= len; i++) {
    if (!is_parindrome(r_read, 0, len - i - 1))
      continue;

    State s = LEFT;
    read_t rst;
    for (int j = len - i; j < len; j++)
      rst.push_back(r_read[j]);
    cands.push_back(make_pair(s, rst));
  }
  if (cands.empty())
    return false;
  // FOREACH (c, cands)
  // LOG(DEBUG, c->first << " " << read_to_str(c->second));
  unsigned id = random_int(cands.size());
  state = cands[id].first;
  rest = cands[id].second;
  return true;
}

bool Model::try_make(Sentence& ret) const {
  vector<Word> right, left;
  State state = BALANCE;
  read_t read;

  id_t center_id;
  read_t center_read;

  // LOG() << "start";
  // unigram.sample(read_t(), center, read);
  if (!sample_center(center_id, center_read, state, read))
    return false;

  // LOG() << "center: " << center << " " << state << " " << center_read;

  std::string center = dictionary.string_of_id(center_id);
  right.push_back(Word(center, center_read));
  left.push_back(Word(center, center_read));

  int depth = 0;

  while (true) {
    depth++;
    if (depth == 30)
      return false;
    // LOG(DEBUG, state << ' ' << read_to_str(read));
    switch (state) {
      case BALANCE: {
        if (!sample_next(true,
                         read, right, left, state, depth < 10))
          return false;
        if (state == BALANCE) {
          if (!sample_next(false,
                           read, right, left, state, depth < 10))
            return false;
          if (state == BALANCE) {
            // success
            FOREACH_REV(p, left) {
              ret.words.push_back(*p);
            }
            FOREACH(p, right) {
              // skip the first pair
              if (p != right.begin()) {
                ret.words.push_back(*p);
              }
            }
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
        if (!sample_next(state == RIGHT,
                         read, right, left, state, true))
          return false;

        bool eos = (state == RIGHT ?
                    right.back().read.empty() :
                    left.back().read.empty());
        if (eos)
          // eos was sampled
          return false;
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
