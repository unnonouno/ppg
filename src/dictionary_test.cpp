#include <gtest/gtest.h>

#include "dictionary.hpp"

namespace ppg {

TEST(Dictionary, trivial) {
  Dictionary d;
  id_t id = d.id_of_string("saitama");
  EXPECT_EQ("saitama", d.string_of_id(id));
  id = d.id_of_string("saitama");
  EXPECT_EQ("saitama", d.string_of_id(id));
}

}  // namespace ppg
