#include <iosfwd>
#include "serializer.hpp"

using namespace std;

class AsciiInSerializer : public InSerializer {
public:
  AsciiInSerializer(istream& in_) : in(in_) {}

  InSerializer& operator >> (int& n);
  InSerializer& operator >> (unsigned& n);
  InSerializer& operator >> (short& n);
  InSerializer& operator >> (char& n);

private:
  istream& in;
};

class AsciiOutSerializer : public OutSerializer {
public:
  AsciiOutSerializer(ostream& out_) : out(out_) {}

  OutSerializer& operator << (int n);
  OutSerializer& operator << (unsigned n);
  OutSerializer& operator << (short n);
  OutSerializer& operator << (char n);
private:
  ostream& out;
};

