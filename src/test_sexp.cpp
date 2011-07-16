#include "test.hpp"

#include <sstream>
#include "sexp.hpp"

namespace sexp {

using namespace std;
/*
template <typename T1, typename T2>
ostream& operator << (ostream& out, pair<T1, T2> const& p) {
  out << '(' << p.first << ", " << p.second << ")";
  return out;
}
*/
TEST_CASE(sexp_save) {
  {
    ostringstream oss;
    save(oss, 1);
    BOOST_CHECK_EQUAL(oss.str(), "1");
  }

  {
    ostringstream oss;
    save(oss, make_pair(1, 2));
    BOOST_CHECK_EQUAL(oss.str(), "(1 2)");
  }

  {
    ostringstream oss;
    save(oss, 1.0);
    BOOST_CHECK_EQUAL(oss.str(), "1");
  }

  {
    ostringstream oss;
    save(oss, 'A');
    BOOST_CHECK_EQUAL(oss.str(), "A");
  }

  {
    ostringstream oss;
    save(oss, "");
    BOOST_CHECK_EQUAL(oss.str(), "");
  }

  {
    ostringstream oss;
    save(oss, "hoge");
    BOOST_CHECK_EQUAL(oss.str(), "hoge");
  }

  {
    ostringstream oss;
    save(oss, "()\\ ");
    BOOST_CHECK_EQUAL(oss.str(), "\\(\\)\\\\\\ ");
  }

  {
    ostringstream oss;
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    save(oss, v);
    BOOST_CHECK_EQUAL(oss.str(), "(1 2 3)");
  }

  {
    ostringstream oss;
    hashmap<string, int> h;
    h["hoge"] = 1;
    h["fuga"] = 2;
    h["foo"] = -1;
    h["var"] = 0;
    save(oss, h);
    BOOST_CHECK_EQUAL(oss.str(), "((hoge 1)(fuga 2)(foo -1)(var 0))");
  }
}

TEST_CASE(sexp_load) {
  {
    istringstream iss("1");
    int x;
    load(iss, x);
    BOOST_CHECK_EQUAL(x, 1);
  }

  {
    istringstream iss("0123");
    int x;
    load(iss, x);
    BOOST_CHECK_EQUAL(x, 123);
  }

  {
    istringstream iss("0");
    int x;
    load(iss, x);
    BOOST_CHECK_EQUAL(x, 0);
  }

  {
    istringstream iss("1.0");
    double x;
    load(iss, x);
    BOOST_CHECK_EQUAL(x, 1.0);
  }

  {
    istringstream iss("01.23");
    double x;
    load(iss, x);
    BOOST_CHECK_EQUAL(x, 1.23);
  }

  {
    istringstream iss("0");
    double x;
    load(iss, x);
    BOOST_CHECK_EQUAL(x, 0);
  }


  {
    try {
      istringstream iss("AA");
      char c;
      load(iss, c);
      BOOST_ERROR( "Should never reach this code!" );
    } catch (InvalidFormat& f) {}
  }

  {
    istringstream iss("(10 2)");
    pair<int, int> p;
    load(iss, p);
    BOOST_CHECK_EQUAL(p.first, 10);
    BOOST_CHECK_EQUAL(p.second, 2);
  }

  {
    istringstream iss("(A 2)");
    pair<char, int> p;
    load(iss, p);
    BOOST_CHECK_EQUAL(p.first, 'A');
    BOOST_CHECK_EQUAL(p.second, 2);
  }

  {
    try {
      istringstream iss("(10 2");
      pair<int, int> p;
      load(iss, p);
      BOOST_ERROR( "Should never reach this code!" );
    } catch (InvalidFormat& f) {}
  }

  {
    try {
      istringstream iss("(10");
      pair<int, int> p;
      load(iss, p);
      BOOST_ERROR( "Should never reach this code!" );
    } catch (InvalidFormat& f) {}
  }


  {
    try {
      istringstream iss("(1 2 3 4)");
      vector<int> v;
      load(iss, v);

      vector<int> r;
      r.push_back(1);
      r.push_back(2);
      r.push_back(3);
      r.push_back(4);

      BOOST_CHECK_EQUAL(v[0], 1);
      BOOST_CHECK_EQUAL(v[1], 2);
      BOOST_CHECK_EQUAL(v[2], 3);
      BOOST_CHECK_EQUAL(v[3], 4);
    } catch (InvalidFormat& f) {}
  }

  {
    istringstream iss("((hoge 1)(fuga 2)(foo -1)(var 0))");
    hashmap<string, int> h;
    load(iss, h);
    BOOST_CHECK_EQUAL(h["hoge"], 1);
    BOOST_CHECK_EQUAL(h["fuga"], 2);
    BOOST_CHECK_EQUAL(h["foo"], -1);
    BOOST_CHECK_EQUAL(h["var"], 0);
  }
}

}
