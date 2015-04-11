#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "util.hpp"

namespace ppg {

TEST(print_vector, empty) {
  std::stringstream ss;
  std::vector<int> v;
  ss << v;
  EXPECT_EQ("[]", ss.str());
}

TEST(print_vector, one) {
  std::stringstream ss;
  std::vector<int> v;
  v.push_back(1);
  ss << v;
  EXPECT_EQ("[1]", ss.str());
}

TEST(print_vector, many) {
  std::stringstream ss;
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  ss << v;
  EXPECT_EQ("[1, 2]", ss.str());
}

}  // namespace ppg
