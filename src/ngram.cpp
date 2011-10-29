#include <elog/elog.h>

#include "Ngram.hpp"
#include "Util.hpp"
#include "HashTrie.hpp"
#include "ArrayTrie.hpp"
#include "Trie.hpp"
#include "Dictionary.hpp"

namespace ppg {

using namespace std;
using pfi::lang::shared_ptr;

string Ngram::none;

bool Ngram::sample(const string& str, const read_t& label,
                   string& r_word, read_t& r_read, bool ignore_eos) const
{
  int id = Dictionary::inst().id_of_string(str);
  LOG() << "sample: " << str << " id: " << id;
  table_t::const_iterator p = table.find(id);
  if (p == table.end())
    return false;
  
  bool r = p->second->sample(label, r_word, r_read, ignore_eos);
  if (r)
    LOG() << "ngram::sample hist:" << str << " word:" << r_word << " read:" <<
        read_to_str(r_read);
  else
    LOG() << "ngram::sample fail";
  return r;
}

void Ngram::insert(const string& history, const string& w, const read_t& r, unsigned count)
{
  int id = Dictionary::inst().id_of_string(history);
  if (!table[id]) {
    //table[id] = new HashTrie();
    table[id] = shared_ptr<Trie>(new ArrayTrie());
  }
  table[id]->insert(r, w, count);
}

void Ngram::swap(Ngram& ngram) {
  table.swap(ngram.table);
}

}
