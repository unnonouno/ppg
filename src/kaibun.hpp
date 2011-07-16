#include "fwd.hpp"

#include <string>
#include "ngram.hpp"
#include "util.hpp"


namespace kaibun {

class Model {
public:
private:
};

bool try_make(const Ngram& forward,
              const Ngram& backward,
              const Trie& unigram,
              vector<pair<string, read_t> >& ret);
}
