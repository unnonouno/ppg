namespace kaibun {


}

int main(int argc, const char** argv) {
  vector<string> args;
  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  using namespace kaibun;
  ifstream file("kaibun.model");
  AsciiInSerializer in(file);
  count << "reading" << endl;
  in >> Dictionary::inst() >> forward >> backward >> unigram;
  cout << "done" << endl;

  
}

