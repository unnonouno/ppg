#include "log.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>

namespace kaibun {

using namespace boost::posix_time;

static enum LOG_LEVEL current_log_level = DEBUG;
static std::ostream* out = &std::cerr;

std::ostream& log(LOG_LEVEL level) {
  if (current_log_level >= level) {
    return *out;
  } else {
    return DevNull::inst();
  }
}

bool loggable(LOG_LEVEL level) {
  return current_log_level >= level;
}

string current_time() {
  typedef boost::date_time::c_local_adjustor<ptime> local_adj;
  //time_duration t = local_adj::utc_to_local(second_clock::local_time()).time_of_day();
  time_duration t = second_clock::local_time().time_of_day();
  return to_simple_string(time_duration(t.hours(), t.minutes(), t.seconds()));
}

void set_log_level(LOG_LEVEL level) {
  current_log_level = level;
}

void set_log_output_stream(std::ostream& o) {
  out = &o;
}

}
