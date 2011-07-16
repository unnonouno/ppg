//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>

#include <iostream>
#include "test.hpp"
#include "hashtrie.hpp"
#include "util.hpp"
#include <sstream>

namespace kaibun {

using namespace std;

TEST_CASE(trie) {
  HashTrie t;
  read_t abc = str_to_read("ABC");
  read_t ab = str_to_read("AB");
  read_t a = str_to_read("A");
  read_t abd = str_to_read("ABD");

  t.insert(abc, "ABC", 1);
  t.print(cout);

  read_t r;
  string w;
  t.get_ith(abc, 0, w, r);
  BOOST_CHECK(w == "ABC");
  BOOST_CHECK(r == abc);

  t.insert(abc, "ABC", 1);

  t.get_ith(ab, 0, w, r);
  BOOST_CHECK(w == "ABC");
  BOOST_CHECK(r == abc);
  t.get_ith(ab, 1, w, r);
  BOOST_CHECK(w == "ABC");
  BOOST_CHECK(r == abc);

  t.insert(abd, "ABD", 1);
  t.get_ith(ab, 0, w, r);
  BOOST_CHECK(w == "ABC");
  BOOST_CHECK(r == abc);
  t.get_ith(ab, 1, w, r);
  BOOST_CHECK(w == "ABC");
  BOOST_CHECK(r == abc);
  t.get_ith(ab, 2, w, r);
  BOOST_CHECK(w == "ABD");
  BOOST_CHECK(r == abd);
  t.print(cout);
  BOOST_CHECK(t.count_total(ab) == 3);
  BOOST_CHECK(t.count_total(a) == 3);
  BOOST_CHECK(t.count_total(abd) == 1);


  t.insert(a, "A", 1);
  t.print(cout);
  t.get_ith(a, 0, w, r);
  BOOST_CHECK(w == "A");
  BOOST_CHECK(r == a);

  t.get_ith(a, 1, w, r);
  BOOST_CHECK(w == "ABC");
  BOOST_CHECK(r == abc);

  t.get_ith(a, 2, w, r);
  BOOST_CHECK(w == "ABC");
  BOOST_CHECK(r == abc);

  t.get_ith(a, 3, w, r);
  BOOST_CHECK(w == "ABD");
  BOOST_CHECK(r == abd);

  /*
  ostringstream oss;
  boost::archive::binary_oarchive oa(oss);
  oa << t;

  HashTrie t2;
  istringstream iss(oss.str());
  boost::archive::binary_iarchive ia(iss);
  ia >> t2;

  t2.get_ith(a, 3, w, r);
  BOOST_CHECK(w == "ABD");
  BOOST_CHECK(r == abd);
  */
}

}
