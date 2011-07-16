class AbstractTrie {
public:
  const string& sample(const vector<char>& read) const;
  
  virtual const string& get_ith(const vector<char>& read, size_t i) const = 0;
  virtual size_t count_total(const vector<char>& read) const = 0;

};

