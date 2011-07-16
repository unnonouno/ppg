#include "test.hpp"

#include <sstream>
#include "asciiserializer.hpp"

using namespace std;

TEST_CASE(ascii_serizlier_base) {

  stringstream ss;
  AsciiOutSerializer out(ss);

  out << 1 << 'a' << 2 << 3 << ' ' << -1;
  
  AsciiInSerializer in(ss);
  int a, b, c, d;
  char z, y;
  in >> a >> z >> b >> c >> y >> d;
  BOOST_CHECK_EQUAL(a, 1);
  BOOST_CHECK_EQUAL(b, 2);
  BOOST_CHECK_EQUAL(c, 3);
  BOOST_CHECK_EQUAL(d, -1);

  BOOST_CHECK_EQUAL(z, 'a');
  BOOST_CHECK_EQUAL(y, ' ');
}

TEST_CASE(ascii_serizlier_string) {
  stringstream ss;
  AsciiOutSerializer out(ss);

  out << string("hogehoge") << "fugafuga" << "hoge fuga" << 1 << "higi";
  string s, t, u, v;
  int n;

  AsciiInSerializer in(ss);
  in >> s >> t >> u >> n >> v;
  BOOST_CHECK_EQUAL("hogehoge", s);
  BOOST_CHECK_EQUAL("fugafuga", t);
  BOOST_CHECK_EQUAL("hoge fuga", u);
  BOOST_CHECK_EQUAL("higi", v);
  BOOST_CHECK_EQUAL(1, n);

}
