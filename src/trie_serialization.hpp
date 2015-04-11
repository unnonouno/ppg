#ifndef TRIE_SERIALIZATION_HPP_6E52F4B3_955D_43EE_94A2_37EEE54A36A7_
#define TRIE_SERIALIZATION_HPP_6E52F4B3_955D_43EE_94A2_37EEE54A36A7_

#include <stdexcept>
#include <string>

#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/serialization.h>

#include "array_trie.hpp"
#include "hash_trie.hpp"

namespace ppg {

template <class A, class T>
pfi::lang::shared_ptr<Trie> load_as(A& a) {
  pfi::lang::shared_ptr<Trie> ptr(new T());
  a & dynamic_cast<T&>(*ptr);
  return ptr;
}

template <class A>
pfi::lang::shared_ptr<Trie> load_trie(A& a) {
  std::string type;
  a & type;
  if (type == "ArrayTrie") {
    return load_as<A, ArrayTrie>(a);
  } else if (type == "HashTrie") {
    return load_as<A, HashTrie>(a);
  } else {
    throw std::runtime_error("unknown type; " + type);
  }
}

template <class A>
void serialize(A &a, pfi::lang::shared_ptr<Trie> &trie) {
  if (a.is_read) {
    trie = load_trie(a);
  } else {
    save_trie(a, *trie);
  }
}

template <class A, class T>
bool try_save(A& a, Trie& trie, const std::string& type) {
  if (typeid(trie) == typeid(T)) {
    std::string name(type);
    a & name
        & dynamic_cast<T&>(trie);
    return true;
  } else {
    return false;
  }
}
template <class A>
void save_trie(A& a, Trie& trie) {
  if (try_save<A, ArrayTrie>(a, trie, "ArrayTrie")) {
  } else if (try_save<A, HashTrie>(a, trie, "HashTrie")) {
  } else {
    throw std::runtime_error(std::string("unknown type: ")
                             + typeid(trie).name());
  }
}

}  // namespace ppg

#endif  // TRIE_SERIALIZATION_HPP_6E52F4B3_955D_43EE_94A2_37EEE54A36A7_
