#include <gtest/gtest.h>

#include "random.hpp"

namespace ppg {

TEST(random, trivial) {
  for (int i = 1; i < 100; i++) {
    int r = random_int(i);
    EXPECT_GT(i, r);
    EXPECT_LE(0, r);
  }
}

}
