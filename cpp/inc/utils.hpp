#pragma once
/* std */
#include <chrono>
#include <string>

namespace Utils {
  template <typename TP>
  time_t to_time_t(TP tp) {
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp - TP::clock::now() + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
  };

  size_t utf8_len(std::string s);
} // namespace Utils
