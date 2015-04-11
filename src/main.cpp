#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <pficommon/data/string/ustring.h>
#include <pficommon/data/serialization.h>
#include <pficommon/text/json.h>

#include "fwd.hpp"
#include "Model.hpp"
#include "Ngram.hpp"
#include "Dictionary.hpp"
#include "Sentence.hpp"
#include "ModelBuilder.hpp"

#include "ReadManager.hpp"
#include "MecabReader.hpp"

#include "cmdline.h"

using namespace std;

namespace ppg {

void proc_mecab(istream& in, Model& model, ReadManager& read_manager) {
  MecabReader reader(in, read_manager);
  ModelBuilder builder;
  size_t count = 0;
  for (Sentence s; reader.get_sentence(s); ) {
    builder.proc_sentence(s);
    count += 1;
    if (count % 100 == 0)
      cout << count << endl;
  }
  builder.swap(model);
}

}

using namespace ppg;

void make_model(const string& model_file) {
  ReadManager read_manager;
  Model model;

  proc_mecab(cin, model, read_manager);

  ofstream file(model_file.c_str());
  pfi::data::serialization::binary_oarchive out(file);
  //pfi::data::serialization::json_oarchive out(file);
  out << Dictionary::inst();
  out << model;
  out << read_manager;
  file.close();
}


string remove_paren(const string& s) {
  if (s.empty())
    return s;
  string ret;
  size_t pos = 0;
  while (true) {
    size_t b = s.find('(', pos);
    if (b == string::npos)
      break;
    size_t e = s.find(')', b);
    if (e == string::npos)
      break;
    ret += s.substr(pos, b - pos);
    pos = e + 1;
  }
  ret += s.substr(pos);
  return ret;
}

void print_sentence(const Sentence& r, ReadManager& read_manager) {
  cout << "----" << endl;
  FOREACH (i, r.words) {
    string s = remove_paren(i->str);
    cout << s << " ";
  }
  cout << endl;
  
  FOREACH (i, r.words) {
    //string s = i->str.substr(0, i->str.find('('));
    string s = i->str;
    cout << s << ":";
    cout << read_manager.read_to_string(i->read);
    cout << " ";
  }
  cout << endl;
}

void make_parindrome(const string& model_name) {
  Model model;
  ReadManager read_manager;
  {
    ifstream file(model_name.c_str());
    pfi::data::serialization::binary_iarchive in(file);
    //pfi::data::serialization::json_iarchive in(file);
    cout << "reading" << endl;
    in >> Dictionary::inst();
    in >> model;
    in >> read_manager;
    cout << "done" << endl;
  }

  cout << "start" << endl;
  while (true) {
    Sentence s;
    if (model.try_make(s)) {
      print_sentence(s, read_manager);
    } else {
      //cout << "fail" << endl;
    }
  }
}

int main(int argc, char* argv[]) {
  cmdline::parser p;
  p.add("make", 'm', "make index");
  p.add<string>("model", 'M', "model file", false, "kaibun.model");

  p.parse_check(argc, argv);

  //LOG::SetDefaultLoggerLevel(LOG::ERROR);

  if (p.exist("make")) {
    make_model(p.get<string>("model"));
  } else {
    make_parindrome(p.get<string>("model"));
  }
}
