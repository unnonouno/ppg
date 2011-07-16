#include "test.hpp"
#include "random.hpp"

namespace kaibun {

TEST_CASE(ngram) {
  Ngram n;
  n.insert("HOGE", "GOH", str_to_read("GOH"));
}

}

