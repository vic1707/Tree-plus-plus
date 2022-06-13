#pragma once
/* std */
#include <array>
#include <ostream>
#include <string_view>
/* fmt */
#include <fmt/format.h>

struct Ratio {
  /* Members */
  size_t num;
  size_t den;
  /* Constructors */
  constexpr Ratio() noexcept : num(1), den(1) {}
  constexpr Ratio(std::uintmax_t n, std::uintmax_t d) noexcept : num(n), den(d) {}
  /* Operators */
  constexpr float operator*(size_t bytes) const noexcept {
    return static_cast<float>(bytes) * static_cast<float>(den) / static_cast<float>(num);
  }
};

struct Unit {
  /* Members */
  Ratio ratio;
  std::string_view name;
  /* Constructors */
  constexpr Unit() noexcept : ratio(), name("B") {}
  constexpr Unit(Ratio r, std::string_view n) noexcept : ratio(r), name(n) {}
};

struct SizeUnit {
  static bool size_in_bytes;
  /* Members */
  size_t bytes;
  Unit unit;
  /* Constructors */
  constexpr SizeUnit() noexcept = default;
  constexpr SizeUnit(size_t b) noexcept : bytes(b) { reload_unit(); };
  /* Methods */
  constexpr float get_human_readable() const noexcept { return unit.ratio * bytes; }
  void reload_unit() noexcept;
  /* Operators */
  void operator+=(size_t b) noexcept {
    bytes += b;
    reload_unit();
  }

  void operator-=(size_t b) noexcept {
    bytes -= b;
    reload_unit();
  }

  friend inline std::ostream &operator<<(std::ostream &os, const SizeUnit &size_unit) noexcept {
    const auto human_readable = fmt::format("{0} {1: >2}", ((double)(int)(size_unit.get_human_readable() * 100) / 100), size_unit.unit.name); // two decimal places
    if (size_in_bytes && size_unit.unit.ratio.num != 1) 
      os << fmt::format("({0} B) - {1: >10}", size_unit.bytes, human_readable);
    else
      os << human_readable;
    return os;
  }

  friend inline constexpr bool operator<(const SizeUnit &lhs, const SizeUnit &rhs) noexcept {
    return lhs.bytes < rhs.bytes;
  }
};
