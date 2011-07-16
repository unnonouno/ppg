#include "sexp.hpp"
#include "boost/lexical_cast.hpp"

namespace sexp {

using namespace std;
using namespace boost;

void save(ostream& out, char c) {
  out << c;
}

void save(ostream& out, int x) {
  out << x;
}

void save(ostream& out, double x) {
  out << x;
}

void save(ostream& out, const string& x) {
  FOREACH (c, x)
    if (*c == '\\')
      out << "\\\\";
    else if (*c == '(')
      out << "\\(";
    else if (*c == ')')
      out << "\\)";
    else if (*c == ' ')
      out << "\\ ";
    else
      out << *c;
}

string read_next(istream& in) {
  string s;
  while (in) {
    char c;
    c = in.get();
    if (!in)
      break;

    if (c == '\\') {
      char c2;
      in >> c2;
      switch (c2) {
      case '\\':
      case '(':
      case ')':
      case ' ':
        s += c2;
        break;
      default:
        throw InvalidFormat("An invalid character proceed a backslash.");
        break;
      }
    } else if (c == ' ') {
      break;
    } else if (c == '(' || c == ')') {
      in.unget();
      break;
    } else {
      s += c;
    }
  }
  return s;
}

void read_begin(istream& in) {
  char c;
  in >> c;
  if (c != '(')
    throw InvalidFormat("'(' does not exist.");
}

void read_end(istream& in) {
  char c;
  in >> c;
  if (c != ')')
    throw InvalidFormat("')' does not exist.");
}

bool can_read_end(istream& in) {
  char c;
  in >> c;
  in.unget();
  return (c == ')');
}

void load(istream& in, int& x) {
  try {
    x = lexical_cast<int>(read_next(in));
  } catch (bad_cast& b) {
    throw InvalidFormat("Cannot regard a next string as a integer number.");
  }
}

void load(istream& in, double& x) {
  try {
    x = lexical_cast<double>(read_next(in));
  } catch (bad_cast& b) {
    throw InvalidFormat("Cannot regard a next string as a double number.");
  }
}

void load(istream& in, char& c) {
  string s = read_next(in);
  if (s.size() != 1)
    throw InvalidFormat(s + " is not a character.");
  c = s[0];
}

void load(istream& in, string& s) {
  s = read_next(in);
}

}

