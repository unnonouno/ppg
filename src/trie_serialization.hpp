#ifndef TRIE_SERIALIZATION_HPP_6E52F4B3_955D_43EE_94A2_37EEE54A36A7_
#define TRIE_SERIALIZATION_HPP_6E52F4B3_955D_43EE_94A2_37EEE54A36A7_

#include <stdexcept>
#include <string>

#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/serialization.h>

#include "array_trie.hpp"
#include "hash_trie.hpp"

namespace ppg {

template <class Ar, class T>
pfi::lang::shared_ptr<Trie> load_as(Ar& ar) {
  pfi::lang::shared_ptr<Trie> ptr(new T());
  ar & dynamic_cast<T&>(*ptr);
  return ptr;
}

template <class Ar>
pfi::lang::shared_ptr<Trie> load_trie(Ar& ar) {
  std::string type;
  ar & type;
  if (type == "ArrayTrie") {
    return load_as<Ar, ArrayTrie>(ar);
  } else if (type == "HashTrie") {
    return load_as<Ar, HashTrie>(ar);
  } else {
    throw std::runtime_error("unknown type; " + type);
  }
}

template <class Ar>
void serialize(Ar& ar, pfi::lang::shared_ptr<Trie> &trie) {
  if (ar.is_read) {
    trie = load_trie(ar);
  } else {
    save_trie(ar, *trie);
  }
}

template <class Ar, class T>
bool try_save(Ar& ar, Trie& trie, const std::string& type) {
  if (typeid(trie) == typeid(T)) {
    std::string name(type);
    ar
        & name
        & dynamic_cast<T&>(trie);
    return true;
  } else {
    return false;
  }
}

template <class Ar>
void save_trie(Ar& ar, Trie& trie) {
  if (try_save<Ar, ArrayTrie>(ar, trie, "ArrayTrie")) {
  } else if (try_save<Ar, HashTrie>(ar, trie, "HashTrie")) {
  } else {
    throw std::runtime_error(std::string("unknown type: ")
                             + typeid(trie).name());
  }
}

}  // namespace ppg

#endif  // TRIE_SERIALIZATION_HPP_6E52F4B3_955D_43EE_94A2_37EEE54A36A7_
