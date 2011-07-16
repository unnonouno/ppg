namespace kaibun {

using namespace std;

class Distribution {
public:
  virtual const string& sample(const vector<char>& read) const = 0;
  
private:
};

}
