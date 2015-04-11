#include "hash_trie.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "util.hpp"

using std::vector;

namespace ppg {

size_t
HashTrie::count_total(
    const vector<char_t>& read,
    bool ignore_empty) const {
  size_t total = iter_count(root, read, 0, 0);
  if (ignore_empty)
    total -= root.n_elements;
  return total;
}

size_t
HashTrie::iter_count(
    const Node& node,
    const vector<char_t>& read,
    size_t pos,
    size_t total) const {
  const size_t t = total + node.n_elements;
  if (pos == read.size())
    return t + node.n_children;
  Node::child_t::const_iterator next =
    node.children.find(read[pos]);
  if (next == node.children.end())
    return t;
  else
    return iter_count(*next->second, read, pos + 1, t);
}


bool
HashTrie::get_ith(
    const read_t& read,
    size_t i,
    id_t& r_word,
    read_t& r_read,
    bool ignore_empty) const {
  r_read.clear();
  if (ignore_empty) {
    i += root.n_elements;
  }
  return iter_get(root, read, 0, i, r_word, r_read);
}

bool
HashTrie::iter_get(
    const Node& node,
    const vector<char_t>& read,
    size_t pos,
    size_t i,
    id_t& r_word,
    read_t& r_read) const {
  if (pos == read.size() || node.n_elements > i) {
    return node.get_ith(i, r_word, r_read);
  }

  Node::child_t::const_iterator next = node.children.find(read[pos]);
  if (next == node.children.end()) {
    return false;
  } else {
    r_read.push_back(read[pos]);
    return iter_get(*next->second, read, pos + 1, i - node.n_elements,
                    r_word, r_read);
  }
}

bool
HashTrie::Node::get_ith(
    size_t i,
    id_t& r_word,
    read_t& r_read) const {
  if (n_elements > i) {
    // found at this node
    FOREACH(e, elements) {
      if (e->first > i) {
        r_word = e->second;
        return true;
      } else {
        i -= e->first;
      }
    }
    throw std::invalid_argument("");
  } else {
    i -= n_elements;
    // perhaps exists under this node
    FOREACH(c, children) {
      if (c->second->n_total() > i) {
        r_read.push_back(c->first);
        return c->second->get_ith(i, r_word, r_read);
      }
      i -= c->second->n_total();
    }
    return false;
  }
}

void
HashTrie::insert(
    const vector<char_t>& read,
    id_t str,
    unsigned n) {
  root.iter_insert(read, 0, str, n);
}

void
HashTrie::Node::iter_insert(
    const read_t& read,
    unsigned i,
    id_t str,
    unsigned n) {
  if (i == read.size()) {
    insert_here(str, n);
  } else {
    n_children += n;
    if (children.count(read[i]) == 0) {
      children[read[i]] = pfi::lang::shared_ptr<Node>(new Node());
    }
    children[read[i]]->iter_insert(read, i + 1, str, n);
  }
}

void
HashTrie::Node::insert_here(id_t str, unsigned n) {
  n_elements += n;
  FOREACH(e, elements) {
    if (e->second == str) {
      e->first += n;
      return;
    }
  }
  elements.push_back(std::make_pair(n, str));
}

void
HashTrie::print(std::ostream& out) const {
  root.iter_print(out, 0);
}

void
HashTrie::Node::iter_print(std::ostream& out, size_t indent) const {
  for (size_t i = 0; i < indent * 2; ++i) {
    out << ' ';
  }
  out << "(e: " << n_elements << ", c: " << n_children << ")" << std::endl;
  FOREACH(c, children) {
    for (size_t i = 0; i < indent * 2; ++i) {
      out << ' ';
    }
    out << c->first << std::endl;
    c->second->iter_print(out, indent + 1);
  }
}

}  // namespace ppg
