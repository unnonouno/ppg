#pragma once

#include <iostream>

using namespace std;

namespace kaibun {

enum LOG_LEVEL { ERROR, WARNING, INFO, DEBUG  };

class DevNull : public ostream {
public:
  /*
  template<class T>
  ostream& operator << (const T& t) {
    return *this;
  }

  ostream& operator << (const char*) {
    return *this;
  }
  */
  ostream& put(char c) {
    return *this;
  }

  static DevNull& inst() {
    static DevNull instance;
    return instance;
  }
};

ostream& log(LOG_LEVEL level = INFO);
void set_log_level(LOG_LEVEL level);
void set_log_output_stream(ostream& out);
string current_time();
bool loggable(LOG_LEVEL level);

#define LOG(level, msg)							\
  loggable(level) && \
  log(level) << '[' << current_time() << ':' << __FILE__ << ':' << __LINE__ << "] " << msg << endl
}
