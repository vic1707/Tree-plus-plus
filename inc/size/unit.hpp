#pragma once
/* CUSTOM */
#include "base.hpp"
/* DEFINE */
using BT = __int128_t;
using LD = long double;
/* STD */
#include <algorithm>
#include <array>
#include <stdexcept>
#include <string_view>

namespace size {
  enum class Unit_Val: const BT {
    /// The basic "byte" unit, used by both base-2 and base-10 styles.
    BYTE = 1,
    /// The base-2 "kibibyte" unit, equal to 1024 bytes.
    KIBIBYTE = BYTE << 10,
    /// The base-10 "kilobyte" unit, equal to 1000 bytes.
    KILOBYTE = 1000 * BYTE,
    /// The base-2 "mebibyte" unit, equal to 1024 kibibytes.
    MEBIBYTE = KIBIBYTE << 10,
    /// The base-10 "megabyte" unit, equal to 1000 kilobytes.
    MEGABYTE = 1000 * KILOBYTE,
    /// The base-2 "gibibyte" unit, equal to 1024 mebibytes.
    GIBIBYTE = MEBIBYTE << 10,
    /// The base-10 "gigabyte" unit, equal to 1000 megabytes.
    GIGABYTE = 1000 * MEGABYTE,
    /// The base-2 "tebibyte" unit, equal to 1024 gibibytes.
    TEBIBYTE = GIBIBYTE << 10,
    /// The base-10 "terabyte" unit, equal to 1000 gigabytes.
    TERABYTE = 1000 * GIGABYTE,
    /// The base-2 "pebibyte" unit, equal to 1024 tebibytes.
    PEBIBYTE = TEBIBYTE << 10,
    /// The base-10 "petabyte" unit, equal to 1000 terabytes.
    PETABYTE = 1000 * TERABYTE,
    /// The base-2 "exbibyte" unit, equal to 1024 pebibytes.
    EXBIBYTE = PEBIBYTE << 10,
    /// The base-10 "exabyte" unit, equal to 1000 petabytes.
    EXABYTE = 1000 * PETABYTE,
    /// The base-2 "zebibyte" unit, equal to 1024 exbibytes.
    ZEBIBYTE = EXBIBYTE << 10,
    /// The base-10 "zettabyte" unit, equal to 1000 exabytes.
    ZETTABYTE = 1000 * EXABYTE,
    /// The base-2 "yobibyte" unit, equal to 1024 zebibytes.
    YOBIBYTE = ZEBIBYTE << 10,
    /// The base-10 "yottabyte" unit, equal to 1000 zettabytes.
    YOTTABYTE = 1000 * ZETTABYTE
  };

  struct Unit {
    const Unit_Val value;
    // styles in order of Style enum (Abbreviated, AbbreviatedLowercase, Full, FullLowercase)
    const std::array<std::string_view, 4> names; 
  };

  constexpr const Unit BYTE = {Unit_Val::BYTE, {"B", "b", "byte", "byte"}};
  constexpr const std::array<const Unit, 16> units = {{
    { Unit_Val::KIBIBYTE, {"KiB", "KiB",  "Kibibyte",  "kibibyte"}},
    { Unit_Val::KILOBYTE, { "KB",  "kB",  "Kilobyte",  "kilobyte"}},
    { Unit_Val::MEBIBYTE, {"MiB", "MiB",  "Mebibyte",  "mebibyte"}},
    { Unit_Val::MEGABYTE, { "MB",  "MB",  "Megabyte",  "megabyte"}},
    { Unit_Val::GIBIBYTE, {"GiB", "GiB",  "Gibibyte",  "gibibyte"}},
    { Unit_Val::GIGABYTE, { "GB",  "GB",  "Gigabyte",  "gigabyte"}},
    { Unit_Val::TEBIBYTE, {"TiB", "TiB",  "Tebibyte",  "tebibyte"}},
    { Unit_Val::TERABYTE, { "TB",  "TB",  "Terabyte",  "terabyte"}},
    { Unit_Val::PEBIBYTE, {"PiB", "PiB",  "Pebibyte",  "pebibyte"}},
    { Unit_Val::PETABYTE, { "PB",  "PB",  "Petabyte",  "petabyte"}},
    { Unit_Val::EXBIBYTE, {"EiB", "EiB",  "Exbibyte",  "exbibyte"}},
    {  Unit_Val::EXABYTE, { "EB",  "EB",   "Exabyte",   "exabyte"}},
    { Unit_Val::ZEBIBYTE, {"ZiB", "ZiB",  "Zebibyte",  "zebibyte"}},
    {Unit_Val::ZETTABYTE, { "ZB",  "ZB", "Zettabyte", "zettabyte"}},
    { Unit_Val::YOBIBYTE, {"YiB", "YiB",  "Yobibyte",  "yobibyte"}},
    {Unit_Val::YOTTABYTE, { "YB",  "YB", "Yottabyte", "yottabyte"}}
  }};

  constexpr const Unit& get_unit(const BT bytes, const int base) {
    if (bytes < static_cast<BT>((units.begin() + base)->value)) return BYTE;

    for (auto it = units.begin() + 2 + base; it < units.end(); std::advance(it, 2))
      if (bytes < static_cast<BT>(it->value)) {
        std::advance(it, -2);
        return *it;
      }
    return units.at(units.size() - 2 + base);
  }
}; // namespace size
