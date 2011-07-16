#include "random.hpp"
#include <ctime>
#include <boost/random.hpp>

namespace kaibun {

using namespace std;
using namespace boost;

mt19937 gen(static_cast<unsigned long>(time(0)));
  
void init_random() {
  
}

int random_int(int m) {
  return uniform_smallint<>(0, m-1)(gen);
}
}
