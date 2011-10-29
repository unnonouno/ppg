#include "ReadNormalizer.hpp"

using namespace pfi::data::string;

namespace ppg {

ReadNormalizer::ReadNormalizer()
    : normalize_map() {
  const ustring unnormalized = string_to_ustring(
      "ガギグゲゴザジズゼゾダヂヅデドバビブベボパピプペポァィゥェォャュョッ");
  const ustring normalized = string_to_ustring(
      "カキクケコサシスセソタチツテトハヒフヘホハヒフヘホアイウエオヤユヤツ");
  for (size_t i = 0; i < unnormalized.size(); ++i) {
    normalize_map[unnormalized[i]] = normalized[i];
  }
}

uchar ReadNormalizer::normalizeChar(uchar ch) const {
  map_t::const_iterator it = normalize_map.find(ch);
  if (it == normalize_map.end()) {
    return ch;
  } else {
    return it->second;
  }
}

}
