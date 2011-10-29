#include "fwd.hpp"

#include <string>
#include <elog/elog.h>
#include "Ngram.hpp"
#include "Util.hpp"
#include "Random.hpp"
//#include "DumpStream.hpp"
#include "Sentence.hpp"
#include "Kaibun.hpp"

namespace ppg {

using namespace std;

/*
DumpStream& operator << (DumpStream& dump, const State& s) {
  switch (s) {
  case BALANCE:
    return dump << "BALANCE";
  case RIGHT:
    return dump << "RIGHT";
  case LEFT:
    return dump << "LEFT";
  }
}
*/
static State op[] = { BALANCE, LEFT, RIGHT };

State opposite(State s) {
  return op[s];
}

bool is_parindrome(const read_t& read,
                   const int l,
                   const int r) {
  for (int il = l, ir = r; il < ir; il++, ir--) {
    if (read[il] != read[ir])
      return false;
  }
  return true;
}

bool Model::sample_next(bool go_right,
                        read_t& read,
                        vector<Word>& right,
                        vector<Word>& left,
                        State& state,
                        bool ignore_eos
                        ) const {
  const vector<Word>& h = go_right ? right : left;
  const string& history = h[h.size() - 1].str;
  LOG() << "kaibun::sample_next:  history: " << history << " read: " << read;

  const unsigned len = read.size();
  const Ngram& ngram = go_right ? forward : backward;

  string r;
  read_t r_read;
  if (!ngram.sample(history, read, r, r_read, ignore_eos))
    return false;
  LOG() << r << r_read;
  const unsigned res_len = r_read.size();
  if (len == res_len) {
    state = BALANCE;
    read.clear();
  } else if (len < res_len) {
    //state = opposite(state);
    state = go_right ? LEFT : RIGHT;
    read.clear();
    for (unsigned i = len; i < res_len; i++)
      read.push_back(r_read[i]);
  } else {
    state = go_right ? RIGHT : LEFT;
    read.erase(read.begin(), read.begin() + res_len);
  }
  LOG() << read;

  if (go_right) {
    right.push_back(Word(r, r_read));
  } else {
    read_t rev(r_read.rbegin(), r_read.rend());
    left.push_back(Word(r, rev));
  }

  return true;
}

bool Model::sample_center(string& r_center,
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
  //FOREACH (c, cands)
  //LOG(DEBUG, c->first << " " << read_to_str(c->second));
  unsigned id = random_int(cands.size());
  state = cands[id].first;
  rest = cands[id].second;
  return true;
}

bool Model::try_make(Sentence& ret) const {
  vector<Word> right, left;
  State state = BALANCE;
  read_t read;

  string center;
  read_t center_read;
  
  LOG() << "start";
  //unigram.sample(read_t(), center, read);
  if (!sample_center(center, center_read, state, read))
    return false;

  LOG() << "center: " << center << " " << state << " " << center_read;

  right.push_back(Word(center, center_read));
  left.push_back(Word(center, center_read));

  int depth = 0;

  while (true) {
    depth++;
    if (depth == 30)
      return false;
    //LOG(DEBUG, state << ' ' << read_to_str(read));
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
            FOREACH_REV (p, left) {
              ret.words.push_back(*p);
            }
            FOREACH (p, right) {
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
          unsigned r = random_int(depth + 3);
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

void Model::swapUnigram(Unigram& unigram) {
  Model::unigram.swap(unigram);
}

void Model::swapForward(Ngram& forward) {
  Model::forward.swap(forward);
}
void Model::swapBackward(Ngram& backward) {
  Model::backward.swap(backward);
}

}

