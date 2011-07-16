namespace kaibun {

class Read : read_t {
public:
  Read(const string&);
  string to_string() const;

private:
  static two_byte_to_read;

};

}
