#include <gtest/gtest.h>
#include "random.hpp"
#include "ngram.hpp"

namespace ppg {

TEST(ngram, trivial) {
  Ngram n;
  n.insert("HOGE", "GOH", str_to_read("GOH"));
}

}

