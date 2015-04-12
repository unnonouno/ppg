#include <string>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "mecab_reader.hpp"
#include "sentence.hpp"

namespace ppg {

TEST(MecabReader, null) {
  std::istringstream in;
  ReadManager rm;
  MecabReader r(in, rm);

  Sentence s;
  EXPECT_FALSE(r.get_sentence(s));
}

TEST(MecabReader, empty) {
  std::istringstream in("EOS");
  ReadManager rm;
  MecabReader r(in, rm);

  Sentence s;
  EXPECT_TRUE(r.get_sentence(s));
  EXPECT_TRUE(s.words.empty());
}

TEST(MecabReader, one) {
  std::istringstream in("トマト\t名詞,一般,*,*,*,*,トマト,トマト,トマト\nEOS");
  ReadManager rm;
  MecabReader r(in, rm);

  Sentence s;
  EXPECT_TRUE(r.get_sentence(s));
  const std::vector<Word>& ws = s.words;
  EXPECT_EQ(1u, ws.size());
  EXPECT_EQ("トマト(名詞:一般)", ws[0].str);
  EXPECT_EQ(3u, ws[0].read.size());
}

}  // namespace ppg

