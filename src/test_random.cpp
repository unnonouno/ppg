#include "test.hpp"
#include "random.hpp"

namespace kaibun {

TEST_CASE(random) {
  for (int i = 1; i < 100; i++) {
    int r = random_int(i);
    BOOST_CHECK(r < i);
    BOOST_CHECK(r >= 0);
  }
}

}
