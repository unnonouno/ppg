#include <gtest/gtest.h>

#include "read_manager.hpp"

using pfi::data::string::ustring;
using pfi::data::string::string_to_ustring;

namespace ppg {

TEST(ReadManager, char) {
  ReadManager m;
  char_t ten = m.uchar_to_char(10);
  EXPECT_EQ(ten, m.uchar_to_char(10));
  EXPECT_EQ(ten, m.uchar_to_char(10));
  char_t eight = m.uchar_to_char(8);
  EXPECT_NE(ten, eight);
  EXPECT_EQ(eight, m.uchar_to_char(8));
  EXPECT_EQ(ten, m.uchar_to_char(10));
}

TEST(ReadManager, empty) {
  ReadManager m;
  read_t r = m.string_to_read("");
  EXPECT_EQ(0U, r.size());

  r = m.ustring_to_read(string_to_ustring(""));
  EXPECT_EQ(0U, r.size());
}

TEST(ReadManager, trivial) {
  ReadManager m;
  ustring ustr = string_to_ustring("あいうえあ");
  read_t r = m.ustring_to_read(ustr);
  EXPECT_EQ(5U, r.size());
  EXPECT_EQ(0, r[0]);
  EXPECT_EQ(1, r[1]);
  EXPECT_EQ(2, r[2]);
  EXPECT_EQ(3, r[3]);
  EXPECT_EQ(0, r[4]);

  EXPECT_EQ(ustr[0], m.char_to_uchar(0));

  EXPECT_EQ(ustr, m.read_to_ustring(r));
}

TEST(ReadManager, normalize) {
  ReadManager m;
  ustring kakiku = string_to_ustring("カキクケコ");
  ustring gagigu = string_to_ustring("ガギグゲゴ");

  read_t read_kakiku = m.ustring_to_read(kakiku);
  read_t read_gagigu = m.ustring_to_read(gagigu);

  EXPECT_EQ(read_kakiku, read_gagigu);
}

}  // namespace ppg
