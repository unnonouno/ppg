#pragma once

#include <string>
#includ "fwd.hpp"

namespace ppg {

class AbstractTrie {
public:
  const std::string& sample(const read_t& read) const;
  
  virtual const std::string& get_ith(const read_t& read,
                                     size_t i) const = 0;
  virtual size_t count_total(const read_t& read) const = 0;
};

}
