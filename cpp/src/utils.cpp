#include "args.hpp"

namespace Utils {
   size_t utf8_len(std::string s) {
    return std::count_if(s.begin(), s.end(),
      [](char c) { return (static_cast<unsigned char>(c) & 0xC0) != 0x80; } );
  }
} // namespace Utils
