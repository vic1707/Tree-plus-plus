#pragma once
/* DEFINE */
using BT = __int128_t;
using LD = long double;
/* STD */
#include <algorithm>
#include <array>
#include <string_view>

namespace size {
  /* BASE */
  /// An enumeration of supported bases to use for generating textual descriptions of sizes.
  /// [`Base::Base10`] is the "usual" units like "kilobyte" and "exabyte", while [`Base::Base2`] is
  /// the SI/memory units like "mebibyte" and "tebibyte", (more often referred to as "MiB" and "TiB",
  /// respectively).
  enum class Base: int {
    /// Base-2 units like "kibibyte" and "mebibyte", more often referred to via their abbreviations
    /// ("KiB" and "MiB", respectively). Each unit is 1024 times greater than the preceding one.
    Base2,
    /// Base-10 units like "kilobyte" and "megabyte", more often referred to via their abbreviations
    /// ("KB" and "MB", respectively). Each unit is 1000 times greater than the preceding one.
    Base10,
  };

  constexpr const Base DEFAULT_BASE = Base::Base2;

  /* STYLE */
  /// An enumeration of supported styles to be used when formatting/printing a [`Size`] type,
  /// specifying how the unit should be spelled out.
  enum class Style: int {
    /// Abbreviated style, e.g. "1024 KB" and "1.29 GiB"
    Abbreviated,
    /// Abbreviated, lowercase style, e.g. "1024 kb" and "1.29 gib"
    AbbreviatedLowercase,
    /// Long unit name style, e.g. "1024 Kilobytes" and "1.29 Gibibytes"
    Long,
    /// Long, lowercase unit name style, e.g. "1024 kilobytes" and "1.29 gibibytes"
    LongLowercase
  };

  constexpr const Style DEFAULT_STYLE = Style::Abbreviated;
  static Style CURRENT_STYLE = DEFAULT_STYLE;

  /* UNIT */
  enum class Unit: const BT {
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

  using Names = std::array<std::string_view, 4>;
  using Unit_Names = std::pair<const Unit, const Names>;
  constexpr const std::array<Unit_Names, 17> units = {{
    {     Unit::BYTE, {  "B",   "b",      "Byte",      "byte"}},
    { Unit::KIBIBYTE, {"KiB", "kib",  "Kibibyte",  "kibibyte"}},
    { Unit::KILOBYTE, { "KB",  "kb",  "Kilobyte",  "kilobyte"}},
    { Unit::MEBIBYTE, {"MiB", "mib",  "Mebibyte",  "mebibyte"}},
    { Unit::MEGABYTE, { "MB",  "mb",  "Megabyte",  "megabyte"}},
    { Unit::GIBIBYTE, {"GiB", "gib",  "Gibibyte",  "gibibyte"}},
    { Unit::GIGABYTE, { "GB",  "gb",  "Gigabyte",  "gigabyte"}},
    { Unit::TEBIBYTE, {"TiB", "tib",  "Tebibyte",  "tebibyte"}},
    { Unit::TERABYTE, { "TB",  "tb",  "Terabyte",  "terabyte"}},
    { Unit::PEBIBYTE, {"PiB", "pib",  "Pebibyte",  "pebibyte"}},
    { Unit::PETABYTE, { "PB",  "pb",  "Petabyte",  "petabyte"}},
    { Unit::EXBIBYTE, {"EiB", "eib",  "Exbibyte",  "exbibyte"}},
    {  Unit::EXABYTE, { "EB",  "eb",   "Exabyte",   "exabyte"}},
    { Unit::ZEBIBYTE, {"ZiB", "zib",  "Zebibyte",  "zebibyte"}},
    {Unit::ZETTABYTE, { "ZB",  "zb", "Zettabyte", "zettabyte"}},
    { Unit::YOBIBYTE, {"YiB", "yib",  "Yobibyte",  "yobibyte"}},
    {Unit::YOTTABYTE, { "YB",  "yb", "Yottabyte", "yottabyte"}}
  }};

  constexpr const Unit_Names& find_unit_pair(const BT bytes, const int base) {
    if (bytes < static_cast<BT>(units.at(1 + base).first)) return units.at(0);

    for (auto unit = 3 + base; unit < units.size(); unit += 2)
      if (bytes < static_cast<BT>(units.at(unit).first))
        return units.at(unit - 2);
    return units.at(units.size() - 2 + base);
  }

  constexpr const Unit_Names& find_unit_pair(const Unit unit) {
    return *std::find_if(units.begin(), units.end(),
      [unit](const Unit_Names& un) { return un.first == unit; });
  }
}; // namespace size