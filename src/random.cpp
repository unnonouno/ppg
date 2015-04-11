#include "random.hpp"

#include <pficommon/math/random.h>

namespace ppg {

pfi::math::random::mtrand rand;

void init_random() {
}

int random_int(int m) {
  return rand.next_int(m);
}

}  // namespace ppg
