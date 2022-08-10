#pragma once
/* std */
#include <algorithm>
#include <chrono>
#include <string_view>

namespace Utils {
  template <typename TP>
  inline time_t to_time_t(TP tp) {
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp - TP::clock::now() + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
  };

  [[nodiscard]] inline constexpr size_t utf8_len(std::string_view s) {
    return std::count_if(s.begin(), s.end(),
      [](char c) { return (static_cast<unsigned char>(c) &0xC0) != 0x80; } );
  }
} // namespace Utils
