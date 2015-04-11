#include <gtest/gtest.h>

#include <pficommon/data/string/ustring.h>

#include "read_normalizer.hpp"

using namespace std;
using namespace pfi::data::string;

namespace ppg {

TEST(ReadNormalizer, trivial) {
  ReadNormalizer n;
  uchar A = string_to_uchar("ア");
  EXPECT_EQ(A, n.normalizeChar(A));

  uchar GA = string_to_uchar("ガ");
  uchar KA = string_to_uchar("カ");
  EXPECT_EQ(KA, n.normalizeChar(GA));
}

}
