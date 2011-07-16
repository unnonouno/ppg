#pragma once

#include "util.hpp"
#include <iostream>
#include <map>
#include "hashmap.hpp"
#include <string>

class DumpStream {
public:
  DumpStream(std::ostream& o) : out(o) {}

  DumpStream& operator << (char c) {
    out << c;
    return *this;
  }

  DumpStream& operator << (short n) {
    out << n;
    return *this;
  }

  DumpStream& operator << (int n) {
    out << n;
    return *this;
  }

  DumpStream& operator << (unsigned n) {
    out << n;
    return *this;
  }

  DumpStream& operator << (const std::string& s) {
    out << s;
    return *this;
  }

private:
  std::ostream& out;
};


template <typename T>
inline
DumpStream& operator << (DumpStream& s, const T& v) {
  v.write(s);
  return s;
}

template <typename T>
inline
DumpStream& operator << (DumpStream& s, const std::vector<T>& v) {
  s << "[";
  FOREACH (it, v) {
    if (it != v.begin())
      s << ", ";
    s << *it;
  }
  s << "]";
  return s;
}

template <typename T, typename S>
inline
DumpStream& operator << (DumpStream& s, const std::pair<T, S>& p) {
  return s << "(" << p.first << ", " << p.second << ")";
}

template <typename M>
inline
void dump_map(DumpStream& s, const M& m) {
  s << "{";
  FOREACH (e, m) {
    s << e->first << ": " << e->second << ", ";
  }
  s << "}";
}

template <typename K, typename V>
inline
DumpStream& operator << (DumpStream& s, const std::map<K, V>& m) {
  dump_map(s, m);
  return s;
}

template <typename K, typename V>
inline
DumpStream& operator << (DumpStream& s, const hashmap<K, V>& m) {
  dump_map(s, m);
  return s;
}

template <typename T>
inline
DumpStream& operator << (DumpStream& s, T* const t) {
  return s << "&" << *t;
}

template <>
inline
DumpStream& operator << (DumpStream& s, const char* t) {
  return s << std::string(t);
}
