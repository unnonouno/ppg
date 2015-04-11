#include "array_trie.hpp"

#include <iostream>
#include <utility>
#include <string>

#include "util.hpp"

using std::pair;
using std::string;

namespace ppg {

bool
ArrayTrie::get_ith(
    const read_t& read,
    size_t i,
    string& r_word,
    read_t& r_read,
    bool ignore_empty) const {
  read_t r;
  FOREACH(c, read) {
    size_t pos = get_begin(r);
    if (pos < data.size() &&
        !(c == read.begin() && ignore_empty) && data[pos].read == r) {
      if (i < get_count(pos)) {
        r_word = data[pos].str;
        r_read = data[pos].read;
        return true;
      } else {
        i -= get_count(pos);
      }
    }
    r.push_back(*c);
  }

  pair<size_t, size_t> range = get_range(read);
  if (ignore_empty && read.empty()
      && range.first < data.size() && data[range.first].read.empty()) {
    range.first++;
  }
  size_t begin = range.first;
  size_t end = range.second;
  unsigned offset = get_offset(begin);
  unsigned goal = offset + i;
  // LOG() << "(" << begin << ", " << end << ")";
  // LOG() << "off(" << get_offset(begin) << ", " << get_offset(end) << ")";

  if (!(goal < get_offset(end))) {
    return false;
  }

  while (end - begin > 1) {
    size_t index = (begin + end) / 2;
    if (get_offset(index) <= goal)
      begin = index;
    else
      end = index;
  }
  r_word = data[begin].str;
  r_read = data[begin].read;
  return true;
}

void
ArrayTrie::insert(const read_t& read, const string& str, unsigned n) {
  size_t pos = get_begin(read);
  if (pos >= data.size() || data[pos].str != str) {
    Node node;
    node.read = read;
    node.str = str;
    node.count = get_offset(pos);
    data.insert(data.begin() + pos, node);
  }
  for (size_t i = pos; i < data.size(); i++)
    data[i].count += n;
}

void
ArrayTrie::print(std::ostream& out) const {
  unsigned last = 0;
  for (size_t i = 0; i < data.size(); i++) {
    out << data[i].str << ": " << (data[i].count - last) << std::endl;
    last = data[i].count;
  }
}

size_t
ArrayTrie::count_total(const read_t& read, bool ignore_empty) const {
  size_t total = 0;
  read_t r;
  // LOG(ERROR, "hist: " << read_to_str(read));
  FOREACH(c, read) {
    size_t pos = get_begin(r);
    if (pos < data.size() &&
        !(c == read.begin() && ignore_empty) &&
        data[pos].read == r) {
      total += get_count(pos);
    }
    r.push_back(*c);
  }

  pair<size_t, size_t> range = get_range(read);
  if (ignore_empty && read.empty()
      && range.first < data.size() && data[range.first].read.empty()) {
    range.first++;
  }
  total += get_offset(range.second) - get_offset(range.first);
  return total;
}

unsigned
ArrayTrie::get_count(size_t pos) const {
  if (data.empty()) {
    return 0;
  } else if (pos == 0) {
    return data[pos].count;
  } else {
    return data[pos].count - data[pos - 1].count;
  }
}

static read_t next_read(const read_t& read) {
  read_t r = read;
  while (r.size() > 0) {
    if (*r.rbegin() == 0xFF) {
      r.pop_back();
    } else {
      r[r.size()-1]++;
      return r;
    }
  }
  return r;
}

pair<size_t, size_t>
ArrayTrie::get_range(const read_t& read) const {
  size_t begin = get_begin(read);
  read_t end_read = next_read(read);
  size_t end;
  if (end_read.size() == 0)
    end = data.size();
  else
    end = get_begin(end_read);
  return std::make_pair(begin, end);
}

size_t
ArrayTrie::get_begin(const read_t& read) const {
  size_t begin = 0, end = data.size();
  while (end - begin > 0) {
    size_t index = (begin + end) / 2;
    if (data[index].read < read) {
      begin = index + 1;
    } else {
      end = index;
    }
  }
  return begin;
}

unsigned
ArrayTrie::get_offset(size_t index) const {
  if (index == 0) {
    return 0;
  } else {
    return data[index - 1].count;
  }
}

}  // namespace ppg
