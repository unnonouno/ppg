#pragma once

namespace ppg {

class Distribution {
public:
  virtual const std::string& sample(const std::vector<char>& read) const = 0;
  
private:
};

}
