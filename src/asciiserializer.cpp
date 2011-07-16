#include <iostream>
#include "asciiserializer.hpp"

using namespace std;

OutSerializer& AsciiOutSerializer::operator << (int n) {
  out << n << ' ';
  return *this;
}

OutSerializer& AsciiOutSerializer::operator << (unsigned n) {
  out << n << ' ';
  return *this;
}

OutSerializer& AsciiOutSerializer::operator << (short n) {
  return (*this) << (int)n;
}

OutSerializer& AsciiOutSerializer::operator << (char n) {
  out << n;
  return *this;
}



InSerializer& AsciiInSerializer::operator >> (int& n) {
  in >> n;
  in.ignore();
  return *this;
}

InSerializer& AsciiInSerializer::operator >> (unsigned& n) {
  in >> n;
  in.ignore();
  return *this;
}

InSerializer& AsciiInSerializer::operator >> (short& n) {
  int m;
  (*this) >> m;
  n = m;
  return *this;
}

InSerializer& AsciiInSerializer::operator >> (char& n) {
  in >> noskipws >> n;
  return *this;
}

