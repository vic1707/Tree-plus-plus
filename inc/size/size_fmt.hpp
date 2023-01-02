#pragma once
/* CUSTOM */
#include "size.hpp"
/* FMT */
#include <fmt/format.h>
/* STD */
#include <array>
#include <cmath>
#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

#define FMT_ENFORCE_COMPILE_STRING

using PositionnalValue = char;
using PositionnalUnit = size::Style;
using Positionnal = std::variant<PositionnalValue, PositionnalUnit, std::nullopt_t>;

constexpr size_t c_strlen(const char *str) {
  auto result = size_t(0);
  while (*(str++) != '\0')
    ++result;
  return result;
}

/* FMT SPEC DEFAULTS */
constexpr const auto DEFAULT_POSITIONNAL_VALUE = 'N'; // `N` for `No format`
constexpr const auto DEFAULT_POSITIONNAL_UNIT = size::Style::Abbreviated;
constexpr const auto DEFAULT_PRECISION = 6; // default precision for floating point numbers see https://en.cppreference.com/w/cpp/io/ios_base/precision
constexpr const auto EMPTY_POSITIONNALS_ARRAY = std::array<Positionnal, 2>{std::nullopt, std::nullopt};

/* FMT Spec for Size library */
/**
  * size_format_spec      ::= [[fill]align][width]["."precision][#][base_modifier][unit_modifier][size_specs]
  * fill                  ::= any character other than '{', '}' and '%'
  * align                 ::= '<' | '>' | '^'
  * width                 ::= integer | "{" [arg_id] "}"
  * precision             ::= integer                                                           ::= will only affect the numbers of decimal places for floating point numbers
  ---------- # -----------
  * base_modifier         ::= 'b' | 'd'                                                         ::= defaults to size::Size::get_base()
  * unit_modifier         ::= 'B' | 'K' | 'M' | 'G' | 'T' | 'P' | 'E' | 'Z' | 'Y'               ::= affects the order of the unit
  * size_specs            ::= [size_specs] unit_specs | [size_specs] value_spec
    * unit_specs          ::= '%' [[style_modifier] | 'U']
      * style_modifier    ::= 'l' | 'L' | 'a' | 'A'                                             ::= affects the style of the unit; defaults to size::Size::get_style()
    * value_spec          ::= '%' [[type] | 'V']                                                ::= affects where the value is displayed
      * type              ::= 'e' | 'f'                                                         ::= affects the representation of the number
**/
template <size::Base unitBase> struct fmt::formatter<size::Size<unitBase>> {
  char format_final[7] = "{:";
  // precision: integer
  std::optional<int> precision;

  // base: 'b' - binary, 'd' - decimal
  size::Base base = unitBase;
  // unit type: 'B' - bytes, 'K' - kilobytes, 'M' - megabytes, 'G' - gigabytes, 'T' - terabytes, 'P' - petabytes, 'E' - exabytes, 'Z' - zettabytes, 'Y' - yottabytes
  // if still not specified, will use the most appropriate unit
  std::optional<size::Unit> unit;
  // positionnal elements
  std::optional<std::array<Positionnal, 2>> positionnals;
  // postitionnal separator
  std::optional<std::string_view> separator;

  [[nodiscard]] constexpr auto parse_positionnal_args(fmt::format_parse_context::iterator it) const -> Positionnal {
    switch (*it) {
      case 'V':
        return DEFAULT_POSITIONNAL_VALUE;
      case 'U':
        return DEFAULT_POSITIONNAL_UNIT;
      case 'l':
        return PositionnalUnit{size::Style::LongLowercase};
      case 'L':
        return PositionnalUnit{size::Style::Long};
      case 'A':
        return PositionnalUnit{size::Style::Abbreviated};
      case 'a':
        return PositionnalUnit{size::Style::AbbreviatedLowercase};
      case 'e':
      case 'E':
      case 'f':
      case 'F':
        return PositionnalValue{*it};
      default:
        throw fmt::format_error("invalid positionnal format");
    }
  }

  template <typename ParseContext>
  [[nodiscard]] constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    auto it = ctx.begin(), end = ctx.end();
    if (it == end || *it == '}') {
      format_final[c_strlen(format_final)] = '}';
      return it;
    }

    // append every it to format_final until we reach a '.' or a '#' or the end
    while (it != end && *it != '.' && *it != '#' && *it != '}')
      format_final[c_strlen(format_final)] = *it++;

    // if we reached a '.', we need to parse the precision
    if (*it == '.') {
      // parse all digits
      precision = 0;
      while (std::isdigit(*++it))
        precision = precision.value() * 10 + (*it - '0');
    }

    // custom spec
    if (*it == '#') {
      ++it;
      // base
      if (*it == 'b' || *it == 'd')
        base = (*it++ == 'b') ? size::Base::Base2 : size::Base::Base10;
      // unit
      if (*it == 'B' || *it == 'K' || *it == 'M' || *it == 'G' || *it == 'T' || *it == 'P' || *it == 'E' || *it == 'Z' || *it == 'Y')
        switch (*it++) {
          case 'B': unit = size::Unit::BYTE; break;
          case 'K': unit = (base == size::Base::Base10) ?  size::Unit::KILOBYTE : size::Unit::KIBIBYTE; break;
          case 'M': unit = (base == size::Base::Base10) ?  size::Unit::MEGABYTE : size::Unit::MEBIBYTE; break;
          case 'G': unit = (base == size::Base::Base10) ?  size::Unit::GIGABYTE : size::Unit::GIBIBYTE; break;
          case 'T': unit = (base == size::Base::Base10) ?  size::Unit::TERABYTE : size::Unit::TEBIBYTE; break;
          case 'P': unit = (base == size::Base::Base10) ?  size::Unit::PETABYTE : size::Unit::PEBIBYTE; break;
          case 'E': unit = (base == size::Base::Base10) ?   size::Unit::EXABYTE : size::Unit::EXBIBYTE; break;
          case 'Z': unit = (base == size::Base::Base10) ? size::Unit::ZETTABYTE : size::Unit::ZEBIBYTE; break;
          case 'Y': unit = (base == size::Base::Base10) ? size::Unit::YOTTABYTE : size::Unit::YOBIBYTE; break;
          default: throw fmt::format_error("invalid unit format (don't know how you got here)");
        }
      // positionnal 1
      if (*it == '%') {
        positionnals.emplace(EMPTY_POSITIONNALS_ARRAY);
        positionnals.value().at(0) = parse_positionnal_args((++it)++);
        // separator
        if (*it != '%') {
          const auto separator_start = it;
          while (it != end && *it != '%' && *it != '}') ++it;
          separator = std::string_view{separator_start, static_cast<size_t>(it - separator_start)};
        } else
          separator = std::string_view{""};
      }
      // positionnal 2
      if (*it == '%')
        positionnals.value().at(1) = parse_positionnal_args((++it)++);
    }

    format_final[c_strlen(format_final)] = '}';

    return it;
  }

  [[nodiscard]] constexpr auto format_value(size::Unit unit_base, int prec, LD ratio, PositionnalValue type) const {
    switch (type) {
    case 'f':
      #ifndef SIZE_KEEP_BYTES_DECIMALS
      if (unit_base == size::Unit::BYTE || prec == 0)
      #else
      if (prec == 0)
      #endif
        return fmt::format("{:.0f}", ratio);
      else
        return fmt::format(
            "{}.{}", (BT)ratio,
            fmt::format("{:.{}f}", fmod(ratio, 1.), prec).substr(2));
    case 'e':
      return fmt::format("{:.{}e}", ratio, prec);
    case 'N':
      return fmt::format("{}", ratio);
    default:
      throw std::invalid_argument("Invalid type for positionnal argument "
                                  "(don't know how you got here)");
    }
  }

  [[nodiscard]] constexpr auto format_unit(size::Names unit_names, PositionnalUnit u) const -> std::string_view {
    return unit_names.at(static_cast<int>(u));
  }

  template <typename FormatContext>
  [[nodiscard]] auto format(const size::Size<unitBase>& s, FormatContext& ctx) const -> decltype(ctx.out()) {
    const auto [unit_base, unit_names] =
        unit.has_value() ? size::find_unit_pair(unit.value())
                         : s.nearest_unit(base);

    const auto& ratio = static_cast<LD>(s.bytes()) / static_cast<LD>(unit_base);

    const auto _positionnals = positionnals.value_or(
        precision.has_value()
            ? std::array<Positionnal, 2>{PositionnalValue{'f'},
                                         DEFAULT_POSITIONNAL_UNIT}
            : std::array<Positionnal, 2>{DEFAULT_POSITIONNAL_VALUE,
                                         DEFAULT_POSITIONNAL_UNIT});

    const auto prec = precision.value_or(DEFAULT_PRECISION);

    auto res = std::string{""};
    for(const auto& pos: _positionnals) {
      if (std::holds_alternative<std::nullopt_t>(pos)) continue;
      if (std::holds_alternative<PositionnalValue>(pos))
        res += format_value(unit_base, prec, ratio, std::get<PositionnalValue>(pos));
      else
        res += format_unit(unit_names, std::get<PositionnalUnit>(pos));

      if (&pos != &_positionnals.back())
        res += separator.value_or(" ");
    }

    return fmt::format_to(ctx.out(), format_final, res);
  }
};
