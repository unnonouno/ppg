#pragma once

#include <string>
#include <vector>
#include <map>

#include "util.hpp"
#include "hashmap.hpp"

using namespace std;

class OutSerializer {
public:
  virtual ~OutSerializer() {}

  virtual OutSerializer& operator << (char c) = 0;
  virtual OutSerializer& operator << (short n) = 0;
  virtual OutSerializer& operator << (int n) = 0;
  virtual OutSerializer& operator << (unsigned n) = 0;
};

class InSerializer {
public:
  virtual ~InSerializer() {}
  virtual InSerializer& operator >> (char& c) = 0;
  virtual InSerializer& operator >> (short & n) = 0;
  virtual InSerializer& operator >> (int & n) = 0;
  virtual InSerializer& operator >> (unsigned & n) = 0;
};

template <typename T>
inline
OutSerializer& operator << (OutSerializer& s, const T& t) {
  t.save(s);
  return s;
}

template <typename T>
inline
InSerializer& operator >> (InSerializer& s, T& t) {
  t.load(s);
  return s;
}

template <>
inline
OutSerializer& operator << (OutSerializer& s, const bool& t) {
  if (t)
    return s << 1;
  else
    return s << 0;
}

template <>
inline
InSerializer& operator >> (InSerializer& s, bool& t) {
  int n;
  s >> n;
  t = (n != 0);
  return s;
}

template <>
inline
OutSerializer& operator << (OutSerializer& s, const size_t& t) {
  return s << (int)t;
}

template <>
inline
InSerializer& operator >> (InSerializer& s, size_t& t) {
  int n;
  s >> n;
  t = n;
  return s;
}

template <>
inline
OutSerializer& operator << (OutSerializer& s, const std::string& t) {
  s << t.size();
  for (unsigned i = 0; i < t.size(); i++)
    s << t[i];
  return s;
}


template <>
inline
InSerializer& operator >> (InSerializer& s, std::string& t) {
  int n;
  s >> n;
  string str(n, ' ');
  for (int i = 0; i < n; i++)
    s >> str[i];
  t = str;
  return s;
}

template <typename T>
inline
OutSerializer& operator << (OutSerializer& s, const std::vector<T>& t) {
  s << t.size();
  for (unsigned i = 0; i < t.size(); i++)
    s << t[i];
  return s;
}

template <typename T>
inline
InSerializer& operator >> (InSerializer& s, std::vector<T>& t) {
  int n;
  s >> n;
  t.resize(n);
  for (unsigned i = 0; i < t.size(); i++)
    s >> t[i];
  return s;
}

template <typename T, typename S>
inline
OutSerializer& operator << (OutSerializer& s, const std::pair<T, S>& t) {
  return s << t.first << t.second;
}

template <typename T, typename S>
inline
InSerializer& operator >> (InSerializer& s, std::pair<T, S>& t) {
  return s >> t.first >> t.second;
}

template <typename M>
inline
void save_map(OutSerializer& s, const M& t) {
  s << t.size();
  FOREACH (e, t) {
    s << e->first << e->second;
  }
}

template <typename K, typename V>
inline
OutSerializer& operator << (OutSerializer& s, const std::map<K, V>& t) {
  save_map(s, t);
  return s;
}

template <typename K, typename V>
inline
OutSerializer& operator << (OutSerializer& s, const hashmap<K, V>& t) {
  save_map(s, t);
  return s;
}


template <typename K, typename V, typename M>
inline
void load_map(InSerializer& s, M& t) {
  int n;
  s >> n;
  for (int i = 0; i < n; i++) {
    K k = K();
    V v = V();
    s >> k >> v;
    t[k] = v;
  }
}

template <typename K, typename V>
inline
InSerializer& operator >> (InSerializer& s, std::map<K, V>& t) {
  load_map<K, V, std::map<K, V> >(s, t);
  return s;
}

template <typename K, typename V>
inline
InSerializer& operator >> (InSerializer& s, hashmap<K, V>& t) {
  load_map<K, V, hashmap<K, V> >(s, t);
  return s;
}


template <typename T>
inline
OutSerializer& operator << (OutSerializer& s, T* const t) {
  if (t)
    return s << true << *t;
  else
    return s << false;
}

template <typename T>
inline
InSerializer& operator >> (InSerializer& s, T*& t) {
  bool non_null;
  s >> non_null;
  if (non_null) {
    t = new T();
    s >> *t;
  }
  return s;
}

template <>
inline
OutSerializer& operator << (OutSerializer& s, const char* t) {
  cerr << "out" << endl;
  return s << string(t);
}

