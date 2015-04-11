#include <gtest/gtest.h>

#include "ngram.hpp"
#include "random.hpp"

namespace ppg {

TEST(ngram, trivial) {
  Ngram n;
  n.insert("HOGE", "GOH", str_to_read("GOH"));
}

}

