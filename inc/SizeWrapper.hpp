#pragma once

#include <iomanip>
#include <fmt/format.h>
#include <size/size.hpp>

inline std::string num_format(LD value) {
  return fmt::format("{}.{}", (int)value,
                     fmt::format("{:.{}f}", fmod(value, 1.), 2).substr(2));
}

struct SizeWrapper: public size::Size {
  static bool size_in_bytes;
  /* Constructors */
  SizeWrapper() noexcept = default;
  SizeWrapper(const size::Size &s) noexcept: size::Size(s) {}
  /* Operators */
  friend inline std::ostream& operator<<(std::ostream& os, const SizeWrapper& s) {
    if (size_in_bytes)
      os << fmt::format("({0} B) - {1: >10}", s.bytes(), fmt::format("{}", static_cast<const size::Size&>(s)));
    else
      os << static_cast<const size::Size&>(s);
    return os;
  }
};

template <> struct fmt::formatter<SizeWrapper> {
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const SizeWrapper& s, FormatContext& ctx) const -> decltype(ctx.out()) {
    return (SizeWrapper::size_in_bytes) 
      ? fmt::format_to(ctx.out(), "({0} B) - {1: >11}", s.bytes(), fmt::format("{}", static_cast<const size::Size&>(s)))
      : fmt::format_to(ctx.out(), "{}", static_cast<const size::Size&>(s));
  }
};

// should be in the base lib
template <> struct fmt::formatter<size::Size> {
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const size::Size& s, FormatContext& ctx) const -> decltype(ctx.out()) {
    const auto& unit = size::get_unit(s.bytes(), static_cast<int>(size::Size::get_base()));
    return fmt::format_to(
        ctx.out(), "{} {}{}",
        num_format(static_cast<LD>(s.bytes()) / static_cast<LD>(unit.value)),
        unit.names.at(static_cast<int>(size::Size::get_style())),
        (static_cast<int>(size::Size::get_style()) > 1 && s.bytes() != 1 ? "s"
                                                                         : "")
    );
  }
};
