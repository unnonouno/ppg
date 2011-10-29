#include "Random.hpp"
#include <pficommon/math/random.h>

namespace ppg {

using namespace std;

pfi::math::random::mtrand rand;
  
void init_random() {
}

int random_int(int m) {
  return rand.next_int(m);
}

}
