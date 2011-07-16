#pragma once

#include "hashmap.hpp"
#include <string>
#include <vector>
#include "util.hpp"

using namespace std;

template <typename K, typename V>
ostream& operator << (ostream& out, const hashmap<K, V>& t) {
  out << "{";
  FOREACH (e, t) {
    if (e != t.begin())
      out << ", ";
    out << e->first << ": " << e->second;
  }
  out << "}";
  return out;
}

template <typename T>
ostream& operator << (ostream& out, const vector<T>& t) {
  out << "[";
  FOREACH (i, t) {
    if (i != t.first)
      out << ", ";
    out << *i;
  }
  out << "]";
  return out;
}

template <typename T>
void write_pointer(ostream& out, const T* t) {
  if (t)
    out << *t;
  else
    out << "NULL";
}

