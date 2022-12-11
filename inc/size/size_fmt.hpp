#pragma once
/* CUSTOM */
#include "size.hpp"
/* FMT */
#include <fmt/format.h>
/* STD */
#include <array>
#include <cmath>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <variant>
#include <vector>
#include <iostream>

#define FMT_ENFORCE_COMPILE_STRING

using PositionnalValue = std::optional<char>;
using PositionnalUnit = std::optional<size::Style>;
using Positionnal = std::variant<PositionnalValue, PositionnalUnit>;

/* FMT SPEC DEFAULTS */
constexpr const auto DEFAULT_POSITIONNAL_VALUE = 'N'; // `N` for `No format`
constexpr const auto DEFAULT_POSITIONNAL_UNIT = size::Style::Abbreviated;
constexpr const auto DEFAULT_PRECISION = 6; // default precision for floating point numbers see https://en.cppreference.com/w/cpp/io/ios_base/precision
const std::vector<Positionnal> DEFAULT_POSITIONNALS_CONFIG = {DEFAULT_POSITIONNAL_VALUE, DEFAULT_POSITIONNAL_UNIT};
const std::vector<std::string> DEFAULT_POSITIONNAL_SEPARATORS_CONFIG = {" "};
constexpr const std::string_view DEFAULT_FILL = " ";
constexpr const std::string_view DEFAULT_ALIGN = ">";

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
  std::string format_final = "{:";
  // precision: integer
  std::optional<int> precision = DEFAULT_PRECISION;

  // base: 'b' - binary, 'd' - decimal
  size::Base base = unitBase;
  // unit type: 'B' - bytes, 'K' - kilobytes, 'M' - megabytes, 'G' - gigabytes, 'T' - terabytes, 'P' - petabytes, 'E' - exabytes, 'Z' - zettabytes, 'Y' - yottabytes
  // if still not specified, will use the most appropriate unit
  std::optional<size::Unit> unit = std::nullopt;
  // positionnal elements
  std::optional<std::vector<Positionnal>> positionnals;
  // postitionnal separator
  std::optional<std::vector<std::string>> positionnal_separators;

  constexpr auto parse_positionnal_args(fmt::format_parse_context::iterator it) -> Positionnal {
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
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    auto it = ctx.begin(), end = ctx.end();
    if (it == end || *it == '}') return it;

    // append every it to format_final until we reach a '.' or a '#' or the end
    while (it != end && *it != '.' && *it != '#')
      format_final += *it++;

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
      // positionnal
      if (*it == '%') {
        positionnals = std::vector<Positionnal>{};
        positionnal_separators = std::vector<std::string>{};
      }
      while (*it == '%') {
        // parse the positionnal argument
        positionnals->emplace_back(parse_positionnal_args((++it)++));
        // if it is end then we exit the loop
        if (it == end) break;
        // if it is already a '%' then we go back to the beginning of the loop
        if (*it == '%' || *it == '}') {
          positionnal_separators->emplace_back("");
          continue;
        }

        const auto separator_start = it;
        while (it != end && *it != '%' && *it != '}') ++it;
        positionnal_separators->emplace_back(std::string(separator_start, it));
      }
    }

    return it;
  }

  template <typename FormatContext>
  auto format(const size::Size<unitBase>& s, FormatContext& ctx) const -> decltype(ctx.out()) {
    std::string res;
    const auto [unit_base, unit_names] = unit.has_value()
                                       ? size::find_unit_pair(unit.value())
                                       : s.nearest_unit(base);
    const auto& ratio = static_cast<LD>(s.bytes()) / static_cast<LD>(unit_base);

    const auto _positionnals = positionnals.value_or(DEFAULT_POSITIONNALS_CONFIG);
    const auto _positionnal_separators = positionnal_separators.value_or(DEFAULT_POSITIONNAL_SEPARATORS_CONFIG);

    auto it_pos = _positionnals.begin();
    auto it_sep = _positionnal_separators.begin();
    const auto end_pos = _positionnals.end();
    const auto end_sep = _positionnal_separators.end();

    for (;it_pos != end_pos; ++it_pos, ++it_sep) {
      if (std::holds_alternative<PositionnalUnit>(*it_pos)) {
        const auto& style = std::get<PositionnalUnit>(*it_pos).value_or(DEFAULT_POSITIONNAL_UNIT);
        res += unit_names.at(static_cast<int>(style));
        // trailing 's'
        if (ratio != 1 && (style == size::Style::Long || style == size::Style::LongLowercase)) res += 's';
      } else if (std::holds_alternative<PositionnalValue>(*it_pos)) {
        const char type = std::get<PositionnalValue>(*it_pos).value_or(DEFAULT_POSITIONNAL_VALUE);
        switch (type) {
          case 'f':
#ifndef SIZE_KEEP_BYTES_DECIMALS
            if (unit_base == size::Unit::BYTE || precision.value() == 0)
#else
            if (precision.value() == 0)
#endif
              res += fmt::format("{:.0f}", ratio);
            else
              res += fmt::format(
                  "{}.{}", (BT)ratio,
                  fmt::format("{:.{}f}",
                              fmod(ratio, 1.),
                              precision.value())
                      .substr(2));
            break;
          case 'e':
            res += fmt::format("{:.{}e}", ratio, precision.value());
            break;
          case 'N':
            res += fmt::format("{}", ratio);
            break;
          default: throw std::invalid_argument("Invalid type for positionnal argument (don't know how you got here)");
        }
      }
      if (it_pos != end_pos && it_sep != end_sep) res += *it_sep;
    }

    return fmt::format_to(
      ctx.out(),
      fmt::runtime(format_final + "}"),
      res
    );
  }
};
