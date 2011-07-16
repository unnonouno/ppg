#include "hashtrie.hpp"
#include "util.hpp"
#include <iostream>
#include <stdexcept>

#include "log.hpp"
#include "dictionary.hpp"
#include "dumpstream.hpp"

namespace kaibun {

const string HashTrie::not_found = "not found";

size_t
HashTrie::count_total(const vector<char_t>& read, bool ignore_empty) const {
  size_t total = iter_count(root, read, 0, 0);
  LOG(DEBUG, total);
  if (ignore_empty)
    total -= root.n_elements;
  return total;
}

size_t
HashTrie::iter_count(const Node& node, const vector<char_t>& read,
                     size_t pos, size_t total) const {
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
HashTrie::get_ith(const read_t& read, size_t i,
                  string& r_word, read_t& r_read, bool ignore_empty) const
{
  r_read.clear();
  if (ignore_empty)
    i += root.n_elements;
  return iter_get(root, read, 0, i, r_word, r_read);
}

bool
HashTrie::iter_get(const Node& node, const vector<char_t>& read,
                   size_t pos, size_t i,
                   string& r_word, read_t& r_read) const {
  if (pos == read.size() || node.n_elements > i)
    return node.get_ith(i, r_word, r_read);

  Node::child_t::const_iterator next = node.children.find(read[pos]);
  if (next == node.children.end())
    return false;
  else {
    r_read.push_back(read[pos]);
    return iter_get(*next->second, read, pos + 1, i - node.n_elements,
                    r_word, r_read);
  }
}

bool
HashTrie::Node::get_ith(size_t i,
                        string& r_word, read_t& r_read) const {
  if (n_elements > i) {
    // found at this node
    FOREACH (e, elements) {
      if (e->first > i) {
        r_word = Dictionary::inst().string_of_id(e->second);
        return true;
      } else
        i -= e->first;
    }
    throw invalid_argument("");
  } else {
    i -= n_elements;
    // perhaps exists under this node
    FOREACH (c, children) {
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
HashTrie::insert(const vector<char_t>& read,
                 const string& str, unsigned n) {
  root.iter_insert(read, 0, str, n);
}

void
HashTrie::Node::iter_insert(const read_t& read,
                            unsigned i,
                            const string& str, unsigned n) {
  if (i == read.size()) {
    insert_here(str, n);
  } else {
    n_children += n;
    if (children.count(read[i]) == 0)
      children[read[i]] = new Node();
    children[read[i]]->iter_insert(read, i + 1, str, n);
  }
}

void
HashTrie::Node::insert_here(const string& str, unsigned n) {
  int id = Dictionary::inst().id_of_string(str);
  n_elements += n;
  FOREACH (e, elements) {
    if (e->second == id) {
      e->first += n;
      return;
    }
  }
  elements.push_back(make_pair(n, id));
}

void
HashTrie::print(ostream& out) const {
  root.iter_print(out, 0);
}

void
HashTrie::Node::iter_print(ostream& out, size_t indent) const {
  out << string(indent * 2, ' ')
      << "(e: " << n_elements << ", c: " << n_children << ")" << endl;
  FOREACH (c, children) {
    out << string(indent * 2, ' ') << c->first << endl;
    c->second->iter_print(out, indent + 1);
  }
}

void
HashTrie::load_s_expression(istream& in) {
  
}

void
HashTrie::Node::save_s_exp(ostream& out) const {
  out << '(' << n_elements << ' ' << n_children << ' ';
  
  out << ')';
}

void
HashTrie::load(InSerializer& in) {
  in >> root;
}

void
HashTrie::save(OutSerializer& out) const {
  out << root;
}

void
HashTrie::Node::load(InSerializer& in) {
  in >> n_elements >> n_children >> elements >> children;
}

void
HashTrie::Node::save(OutSerializer& out) const {
  out << n_elements << n_children << elements << children;
}


void
HashTrie::write(DumpStream& out) const {
  out << root;
}

void
HashTrie::Node::write(DumpStream& out) const {
  //  out << "# elem: " << n_elements << '\n';
  //  out << "# child: " << n_children << '\n';
  out << "{{elem: " << elements << ", " << "child: " << children << "}}";
}

}
