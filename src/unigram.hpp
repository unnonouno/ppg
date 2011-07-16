namespace kaibun {

using namespace std;

class Unigram {
public:
  void insert(const string& w, const read_t& r);

  void sample(string& w, read_t& r) const;
private:
  Trie trie;
};

}
