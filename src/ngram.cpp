#include "ngram.hpp"
#include "util.hpp"
#include "hashtrie.hpp"
#include "arraytrie.hpp"
#include "log.hpp"
#include "dumpstream.hpp"

namespace kaibun {

using namespace std;


string Ngram::none;

Ngram::~Ngram() {
  FOREACH (p, table)
    delete p->second;
}

bool Ngram::sample(const string& str, const read_t& label,
                   string& r_word, read_t& r_read, bool ignore_eos) const
{
  int id = Dictionary::inst().id_of_string(str);
  LOG(DEBUG, "sample: " << str << " id: " << id);
  table_t::const_iterator p = table.find(id);
  if (p == table.end())
    return false;
  
  bool r = p->second->sample(label, r_word, r_read, ignore_eos);
  if (r)
    LOG(DEBUG, "ngram::sample hist:" << str << " word:" << r_word << " read:" <<
        read_to_str(r_read));
  else
    LOG(DEBUG, "ngram::sample fail");
  return r;
}

void Ngram::insert(const string& history, const string& w, const read_t& r, unsigned count)
{
  int id = Dictionary::inst().id_of_string(history);
  if (!table[id])
    //table[id] = new HashTrie();
    table[id] = new ArrayTrie();
  table[id]->insert(r, w, count);
}

void Ngram::save(OutSerializer& out) const {
  out << table;
}

void Ngram::load(InSerializer& in) {
  in >> table;
  LOG(DEBUG, "load table: " << table.size());
}

void Ngram::write(DumpStream& out) const {
  //out << "ngram:" << '\n';
  LOG(DEBUG, "load table: " << table.size());
  out << table << '\n';
}

}
