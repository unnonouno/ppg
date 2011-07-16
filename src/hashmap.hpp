#pragma once

#include <ext/hash_map>
#include <boost/functional/hash.hpp>

template <typename K, typename V>
class hashmap : public __gnu_cxx::hash_map<K, V, boost::hash<K> > {
};

