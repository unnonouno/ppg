#pragma once

#include <iosfwd>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "util.hpp"
#include "hashmap.hpp"

namespace sexp {

using namespace std;

class InvalidFormat : public runtime_error {
public:
  InvalidFormat(const string& arg) : runtime_error(arg) {}
};

void save(ostream& out, char c);

void save(ostream& out, int x);

void save(ostream& out, double x);

void save(ostream& out, const string& x);

template <typename T1, typename T2>
void save(ostream& out, const pair<T1, T2>& p) {
  out << '(';
  save(out, p.first);
  out << ' ';
  save(out, p.second);
  out << ')';
}

template <typename T>
void save(ostream& out, const vector<T>& v) {
  out << '(';
  FOREACH (x, v) {
    if (x != v.begin())
      out << ' ';
    out << *x;
  }
  out << ')';
}

template <typename M>
void save_map(ostream& out, const M& h) {
  out << '(';
  FOREACH (p, h) {
    out << '(';
    save(out, p->first);
    out << ' ';
    save(out, p->second);
    out << ')';
  }
  out << ')';
}

template <typename K, typename V>
void save(ostream& out, const hashmap<K, V>& h) {
  save_map(out, h);
}

template <typename K, typename V>
void save(ostream& out, const map<K, V>& h) {
  save_map(out, h);
}

//
void read_begin(istream& in);

void read_end(istream& in);

bool can_read_end(istream& in);

void load(istream& in, int& x);

void load(istream& in, double& x);

void load(istream& in, char& c);

void load(istream& in, string& s);

template <typename T1, typename T2>
void load(istream& in, pair<T1, T2>& p) {
  read_begin(in);
  load(in, p.first);
  load(in, p.second);
  read_end(in);
}

template <typename T>
void load(istream& in, vector<T>& v) {
  read_begin(in);
  while (!can_read_end(in)) {
    T x;
    load(in, x);
    v.push_back(x);
  }
  read_end(in);
}

template <typename K, typename V, typename M>
void load_map(istream& in, M& m) {
  read_begin(in);
  while (!can_read_end(in)) {
    pair<K, V> p;
    load(in, p);
    m[p.first] = p.second;
  }
  read_end(in);
}

template <typename K, typename V>
void load(istream& in, hashmap<K, V>& h) {
  load_map<K, V, hashmap<K, V> >(in, h);
}

template <typename K, typename V>
void load(istream& in, map<K, V>& h) {
  load_map<K, V, map<K, V> >(in, h);
}


}

