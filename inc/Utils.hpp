#pragma once
/* std */
#include <algorithm>
#include <chrono>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

namespace Utils {
  template <typename TP>
  inline time_t to_time_t(TP tp) {
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp - TP::clock::now() + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
  };

  [[nodiscard]] inline size_t utf8_len(std::string_view s) {
    return std::count_if(s.begin(), s.end(),
      [](char c) { return (static_cast<unsigned char>(c) &0xC0) != 0x80; } );
  }

  inline void char_to_lower(char& c) { c = std::tolower(c); };
  inline void word_to_lower(std::string& w) {
    std::for_each(w.begin(), w.end(), char_to_lower);
  }


  template <typename T>
  concept Item = std::same_as<T, std::string> || std::same_as<T, std::string_view>;

  template <typename T>
  concept Delim = std::same_as<T, char> || std::same_as<T, std::string> || std::same_as<T, std::string_view>;

  template <Item T, Delim D>
  [[nodiscard]] inline std::vector<T> split_v(const T& s, D delimiter) {
    size_t pos_start = 0, pos_end, delim_len;
    if constexpr (std::same_as<D, char>) {
      delim_len = 1;
    } else {
      delim_len = delimiter.length();
    }
    T token;
    std::vector<T> res;

    while ((pos_end = s.find (delimiter, pos_start)) != T::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.insert(res.end(), token);
    }

    res.insert(res.end(), s.substr(pos_start));
    return res;
  }

  template <Item T, Delim D>
  [[nodiscard]] inline std::unordered_set<T> split_us(const T& s, D delimiter) {
     size_t pos_start = 0, pos_end, delim_len;
    if constexpr (std::same_as<D, char>) {
      delim_len = 1;
    } else {
      delim_len = delimiter.length();
    }
    T token;
    std::unordered_set<T> res;

    while ((pos_end = s.find (delimiter, pos_start)) != T::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.insert(res.end(), token);
    }

    res.insert(res.end(), s.substr(pos_start));
    return res;
  }
} // namespace Utils
