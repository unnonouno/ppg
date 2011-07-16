#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "fwd.hpp"
#include "kaibun.hpp"
#include "ngram.hpp"
#include "hashtrie.hpp"
#include "log.hpp"
#include "dictionary.hpp"

#include "asciiserializer.hpp"
#include "dumpstream.hpp"

namespace kaibun {

vector<string> split(const string& s, const string& delim) {
  unsigned pos = 0;
  vector<string> ret;
  while (true) {
    unsigned next = s.find_first_of(delim, pos);
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

string two_byte_to_string(unsigned w) {
  char c1 = w >> 8;
  char c2 = w & 0xFF;
  return string() + c1 + c2;
}

unsigned get_two_byte(const string& s, unsigned pos) {
  unsigned w = (static_cast<unsigned>(s[pos]) << 8)
    | (static_cast<unsigned>(s[pos + 1]) & 0xFF);
  static int n = 0;
  if (n < 10) {
    cout << s.substr(pos, 2) << ": " << w << ": " << two_byte_to_string(w) << endl;
    n++;
  }
  return w;
}

static hashmap<unsigned, char_t> two_byte_to_char_table;
static char_t last_char = 0;

char two_byte_to_char(unsigned w) {
  if (two_byte_to_char_table.count(w) == 0) {
    two_byte_to_char_table[w] = last_char++;
  }
  return two_byte_to_char_table[w];
}

void show_two_byte_table() {
  FOREACH (it, two_byte_to_char_table) {
    cout << two_byte_to_string(it->first) << ": " << it->second << endl;
  }
}

static const string unnormalized = 
"ガギグゲゴザジズゼゾダヂヅデドバビブベボパピプペポァィゥェォャュョッ";
static const string normalized =
"カキクケコサシスセソタチツテトハヒフヘホハヒフヘホアイウエオヤユヤツ";
char normalize_char(char c) {
  for (unsigned i = 0; i < unnormalized.size(); i += 2) {
    unsigned u = get_two_byte(unnormalized, i);
    if (two_byte_to_char(u) == c) {
      unsigned n = get_two_byte(normalized, i);
      return two_byte_to_char(n);
    }
  }
  return c;
}

read_t normalize_read(const read_t& read) {
  read_t normalized_read;
  FOREACH (r, read) {
    normalized_read.push_back(normalize_char(*r));
  }
  return normalized_read;
}


read_t two_byte_to_read(const string& str) {
  read_t read;
  for (unsigned i = 0; i < str.size(); i += 2) {
    unsigned w = get_two_byte(str, i);
    read.push_back(two_byte_to_char(w));
  }
  LOG(DEBUG, str << ": " << read_to_str(read));
  return normalize_read(read);
  //return read;
}
/*
void proc_mecab(istream& in, Ngram& forward, Ngram& backward, HashTrie& unigram) {
  string line;
  string last = "";
  read_t last_read;
  int count = 0;
  while (getline(in, line)) {
    count++;
    if (count % 10000 == 0)
      cout << "# of line: " << count << endl;
    string str;
    read_t read;

    vector<string> ss = split(line, "\t");
    if (line == "EOS" || ss.size() < 2) {
      if (last == "")
        continue;
    } else {
      str = ss[0];
      vector<string> features = split(ss[1], ",");
      read = two_byte_to_read(features[features.size() - 2]);
    }

    if (str == "" || !read.empty()) {
      forward.insert(last, str, read);
      if (str != "")
        unigram.insert(read, str, 1);
    }
    if (last == "" || !last_read.empty()) {
      backward.insert(str, last, last_read);
    }

    last = str;
    last_read = read;
    reverse(last_read.begin(), last_read.end());
  }
  cout << "done" << endl;
}
*/
void proc_mecab(istream& in, Ngram& forward, Ngram& backward, HashTrie& unigram) {
  map<pair<read_t, string>, unsigned> unigram_map;
  map<string, map<pair<read_t, string>, unsigned> > forward_map;
  map<string, map<pair<read_t, string>, unsigned> > backward_map;
  string line;
  string last = "";
  read_t last_read;
  int count = 0;
  while (getline(in, line)) {
    count++;
    if (count % 10000 == 0)
      cout << "# of line: " << count << endl;
    string str;
    read_t read;

    vector<string> ss = split(line, "\t");
    if (line == "EOS" || ss.size() < 2) {
      if (last == "")
        continue;
    } else {
      str = ss[0];
      vector<string> features = split(ss[1], ",");
      string pos = features[0] + ":" + features[1];

      read = two_byte_to_read(features[features.size() - 2]);
      if (read.empty() || str == "…") {
        last = "";
        continue;
      }
      str = str + "(" + pos + ")";
    }

    LOG(DEBUG, "str: " << str);
    if (str == "" || !read.empty()) {
      forward_map[last][make_pair(read, str)] += 1;
      if (str != "")
        unigram_map[make_pair(read, str)] += 1;
    }
    if (last == "" || !last_read.empty()) {
      backward_map[str][make_pair(last_read, last)] += 1;
    }

    last = str;
    last_read = read;
    reverse(last_read.begin(), last_read.end());
  }

  FOREACH (it, unigram_map) {
    unigram.insert(it->first.first, it->first.second, it->second);
  }
  FOREACH (it, forward_map) {
    FOREACH (it2, it->second) {
      //if (it2->second >= 4)
        forward.insert(it->first, it2->first.second, it2->first.first, it2->second);
    }
  }
  FOREACH (it, backward_map) {
    FOREACH (it2, it->second) {
      //      if (it2->second >= 4)
        backward.insert(it->first, it2->first.second, it2->first.first, it2->second);
    }
  }

  cout << "done" << endl;
  show_two_byte_table();
}


}

int main(int argc, const char** argv) {
  vector<string> args;
  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  using namespace kaibun;
  set_log_level(ERROR);

  Ngram forward;
  Ngram backward;
  HashTrie unigram;

  if (args.size() > 1 && args[1] == "-m") {
    proc_mecab(cin, forward, backward, unigram);

    DumpStream dump(cout);
    forward.write(dump);


    ofstream file("kaibun.model");
    AsciiOutSerializer out(file);
    out << Dictionary::inst() << forward << backward << unigram;
    file.close();
  } else {
    ifstream file("kaibun.model");
    AsciiInSerializer in(file);
    cout << "reading" << endl;
    in >> Dictionary::inst() >> forward >> backward >> unigram;
    cout << "done" << endl;

    DumpStream dump(cout);
    dump << unigram;

    cout << "start" << endl;
    while (true) {
      vector<pair<string, read_t> > r;
      bool success = try_make(forward, backward, unigram, r);
      if (success) {
        cout << "----" << endl;
        FOREACH (i, r) {
          string s = i->first.substr(0, i->first.find('('));
          cout << s << " ";
        }
        cout << endl;

        FOREACH (i, r) {
          //string s = i->first.substr(0, i->first.find('('));
          string s = i->first;
          cout << s << ":";

          for(unsigned j=0;j<i->second.size();j++)
            cout << i->second[j] << "-";
          /*
          cout<<endl;
          */
          cout << " ";
        }
        //break;
      } else {
        //cout << "fail" << endl;
      }
    }
  }
}
