#pragma once

#include <vector>
#include <string>
#include <iosfwd>
#include "fwd.hpp"
#include "hashmap.hpp"
#include <iosfwd>
#include "trie.hpp"
#include "util.hpp"
//#include <boost/serialization/export.hpp>
//#include <boost/serialization/vector.hpp>

#include "serializer.hpp"

namespace kaibun {

using namespace std;

/**
 * hashmap ���g���� TRIE �����D
 *
 */
class HashTrie : public Trie {
public:
  virtual ~HashTrie() {}

  /**
   * �ǂݕ��� read �̕���������C�������� read ���܂ޕ�����ł���P��W���̓��C
   * i �Ԗڂ̒P���Ԃ��D
   * @return r_word   i �Ԗڂ̒P��̎���
   * @return r_read   i �Ԗڂ̒P��̓ǂ�
   */
  bool get_ith(const read_t& read, size_t i, string& r_word, read_t& r_read,
               bool ignore_empty = false) const;

  /**
   * �P��� TRIE �ɒǉ�����D
   *
   */
  void insert(const read_t& read, const string& str, unsigned n);

  size_t count_total(const read_t& read, bool ignore_empty = false) const;

  void print(ostream& out) const;

  void load_s_expression(istream& in);

  void save_s_expression(ostream& out) const;

  void load(InSerializer& in);
  void save(OutSerializer& out) const;
  void write(DumpStream& out) const;


private:
  struct Node;

  static const string not_found;

  size_t
  iter_count(const Node& node, const read_t& read,
             size_t pos, size_t total) const;

  bool
  iter_get(const Node& node, const read_t& read,
           size_t pos, size_t i,
           string& r_word, read_t& r_read) const;


  struct Node {
    typedef hashmap<char_t, struct Node*> child_t;

    bool get_ith(size_t i, string& r_word, read_t& r_read) const;
    
    void
    iter_insert(const vector<char_t>& read, const string& str,
                unsigned n, size_t id);

    Node() :
      n_elements(0), n_children(0), elements(), children() {}

    unsigned n_total() const {
      return n_elements + n_children;
    }

    void insert_here(const string& str, unsigned n);

    void iter_insert(const read_t& read, unsigned i, const string& str, unsigned n);

    void save_s_exp(ostream& out) const;


    void
    iter_print(ostream& out, size_t indent) const;

    unsigned n_elements;
    unsigned n_children;
    vector<pair<unsigned, int> > elements;
    child_t children;

    void load(InSerializer& in);
    void save(OutSerializer& out) const;
    void write(DumpStream& out) const;

  private:
    /*
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & n_elements & n_children & elements & children;
    }
    */
  } root;

  /*
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar & root;
  }
  */
};

}

//BOOST_CLASS_EXPORT_GUID(kaibun::HashTrie, "HashTrie");

