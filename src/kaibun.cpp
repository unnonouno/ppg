#include "fwd.hpp"

#include <string>
#include "ngram.hpp"
#include "util.hpp"
#include "random.hpp"
#include "log.hpp"
#include "dumpstream.hpp"

namespace kaibun {

using namespace std;

enum State {
  BALANCE, RIGHT, LEFT
};
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

bool is_palindorome(const read_t& read,
                    const unsigned l,
                    const unsigned r) {
  for (unsigned il = l, ir = r; il < ir; il++, ir--) {
    if (read[il] != read[ir])
      return false;
  }
  return true;
}

bool sample_next(const Ngram& forward,
                 const Ngram& backward,
                 bool go_right,
                 read_t& read,
                 vector<pair<string, read_t> >& right,
                 vector<pair<string, read_t> >& left,
                 State& state,
                 bool ignore_eos
                 ) {
  const vector<pair<string, read_t> >& h =
    go_right ? right : left;
  const string& history = h[h.size() - 1].first;
  LOG(DEBUG, "kaibun::sample_next:  history: " << history << " read: " << read);

  const unsigned len = read.size();
  const Ngram& ngram = go_right ? forward : backward;

  string r;
  read_t r_read;
  if (!ngram.sample(history, read, r, r_read, ignore_eos))
    return false;
  LOG(DEBUG, r << r_read);
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
  LOG(DEBUG, read);

  if (go_right)
    right.push_back(make_pair(r, r_read));
  else
    left.push_back(make_pair(r, r_read));

  return true;
}

bool sample_center(const Trie& unigram,
                   string& r_center, read_t& r_read,
                   State& state, read_t& rest) {
  if (!unigram.sample(read_t(), r_center, r_read))
    return false;

  const int len = static_cast<int>(r_read.size());
  vector<pair<State, read_t> > cands;

  for (int i = 0; i <= len; i++) {
    int l = i, r = len - 1;
    bool ok = true;
    while (l < r)
      if (r_read[l++] != r_read[r--])
        ok = false;
    if (!ok) continue;

    State s = RIGHT;
    read_t rst;
    for (int j = i - 1; j >= 0; j--)
      rst.push_back(r_read[j]);
    if (i == 0) s = BALANCE;
    cands.push_back(make_pair(s, rst));
  }

  for (int i = 1; i <= len; i++) {
    int l = 0, r = len - i - 1;
    bool ok = true;
    while (l < r)
      if (r_read[l++] != r_read[r--])
        ok = false;
    if (!ok) continue;

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

bool try_make(const Ngram& forward,
              const Ngram& backward,
              const Trie& unigram,
              vector<pair<string, read_t> >& ret) {

  vector<pair<string, read_t> > right, left;
  State state = BALANCE;
  read_t read;

  string center;
  read_t center_read;
  
  LOG(DEBUG, "start");
  //unigram.sample(read_t(), center, read);
  if (!sample_center(unigram, center, center_read, state, read))
    return false;

  LOG(DEBUG, "center: " << center << " " << state << " " << center_read);

  right.push_back(make_pair(center, center_read));
  left.push_back(make_pair(center, center_read));

  int depth = 0;

  while (true) {
    depth++;
    if (depth == 30)
      return false;
    //LOG(DEBUG, state << ' ' << read_to_str(read));
    switch (state) {
    case BALANCE: {
      if (!sample_next(forward, backward, true,
                       read, right, left, state, depth < 10))
        return false;
      if (state == BALANCE) {
        if (!sample_next(forward, backward, false,
                         read, right, left, state, depth < 10))
          return false;
        if (state == BALANCE) {
          // success
          FOREACH_REV (p, left)
            ret.push_back(*p);
          FOREACH (p, right)
            // skip the first pair
            if (p != right.begin())
              ret.push_back(*p);
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
      if (!sample_next(forward, backward, state == RIGHT,
                       read, right, left, state, true))
        return false;
      
      bool eos = (state == RIGHT ?
                  right.back().second.empty() :
                  left.back().second.empty());
      if (eos)
        // eos was sampled
        return false;
    }
      break;
    }
  }
}

}

