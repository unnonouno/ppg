#ifndef HASH_TRIE_HPP_AF7AB88E_ECB6_4F95_AE99_C5939CFEFA70_
#define HASH_TRIE_HPP_AF7AB88E_ECB6_4F95_AE99_C5939CFEFA70_

#include <iosfwd>
#include <string>
#include <vector>

#include <pficommon/lang/shared_ptr.h>
#include <pficommon/data/unordered_map.h>
#include <pficommon/data/serialization.h>

#include "fwd.hpp"
#include "trie.hpp"
#include "util.hpp"

namespace ppg {

/**
 * Trie implementation using Hash table.
 *
 */
class HashTrie : public Trie {
public:
  virtual ~HashTrie() {}

  bool get_ith(const read_t& read,
               size_t i,
               std::string& r_word,
               read_t& r_read,
               bool ignore_empty = false) const;

  void insert(const read_t& read,
              const std::string& str,
              unsigned n);

  size_t count_total(const read_t& read, bool ignore_empty = false) const;

  void print(std::ostream& out) const;

  struct Node;

private:
  friend class pfi::data::serialization::access;
  template <class A>
  void serialize(A &a) {
    a & root;
  }

  static const std::string not_found;

  size_t
  iter_count(const Node& node,
             const read_t& read,
             size_t pos,
             size_t total) const;

  bool
  iter_get(const Node& node,
           const read_t& read,
           size_t pos,
           size_t i,
           std::string& r_word,
           read_t& r_read) const;

 public:
  struct Node {
    typedef pfi::data::unordered_map<char_t, pfi::lang::shared_ptr<Node> > child_t;

    bool get_ith(size_t i, std::string& r_word, read_t& r_read) const;
    
    void
    iter_insert(const std::vector<char_t>& read,
                const std::string& str,
                unsigned n,
                size_t id);

    Node() :
      n_elements(0), n_children(0), elements(), children() {}

    unsigned n_total() const {
      return n_elements + n_children;
    }

    void insert_here(const std::string& str, unsigned n);

    void iter_insert(const read_t& read, unsigned i, const std::string& str, unsigned n);

    void iter_print(std::ostream& out, size_t indent) const;

    unsigned n_elements;
    unsigned n_children;
    std::vector<std::pair<unsigned, int> > elements;
    child_t children;

    friend class pfi::data::serialization::access;
    template <class A>
    void serialize(A &a) {
      a & n_elements & n_children & elements & children;
    }
  } root;

};

template <class A>
void serialize(A &a, pfi::lang::shared_ptr<HashTrie::Node> &node) {
  bool not_null = false;
  if (a.is_read) {
    a & not_null;
    if (not_null)
      a & *node;
  } else {
    if (node) {
      not_null = true;
      a & not_null;
      a & *node;
    } else {
      a & not_null;
    }
  }
}

}

#endif  // HASH_TRIE_HPP_AF7AB88E_ECB6_4F95_AE99_C5939CFEFA70_
