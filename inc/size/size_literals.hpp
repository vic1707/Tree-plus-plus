#pragma once
/* CUSTOM */
#include "size.hpp"

using ULL = unsigned long long;

namespace size::size_literals {
  // Base-10 units
  inline constexpr auto operator""_B (ULL      bytes) noexcept -> Size { return {bytes}; }
  inline constexpr auto operator""_KB(ULL  kilobytes) noexcept -> Size { return { kilobytes *  static_cast<BT>(Unit_Val::KILOBYTE)}; }
  inline constexpr auto operator""_MB(ULL  megabytes) noexcept -> Size { return { megabytes *  static_cast<BT>(Unit_Val::MEGABYTE)}; }
  inline constexpr auto operator""_GB(ULL  gigabytes) noexcept -> Size { return { gigabytes *  static_cast<BT>(Unit_Val::GIGABYTE)}; }
  inline constexpr auto operator""_TB(ULL  terabytes) noexcept -> Size { return { terabytes *  static_cast<BT>(Unit_Val::TERABYTE)}; }
  inline constexpr auto operator""_PB(ULL  petabytes) noexcept -> Size { return { petabytes *  static_cast<BT>(Unit_Val::PETABYTE)}; }
  inline constexpr auto operator""_EB(ULL   exabytes) noexcept -> Size { return {  exabytes *   static_cast<BT>(Unit_Val::EXABYTE)}; }
  inline constexpr auto operator""_ZB(ULL zettabytes) noexcept -> Size { return {zettabytes * static_cast<BT>(Unit_Val::ZETTABYTE)}; }
  inline constexpr auto operator""_YB(ULL yottabytes) noexcept -> Size { return {yottabytes * static_cast<BT>(Unit_Val::YOTTABYTE)}; }
  // Base-2 units
  inline constexpr auto operator""_KiB(ULL kibibytes) noexcept -> Size { return {kibibytes * static_cast<BT>(Unit_Val::KIBIBYTE)}; }
  inline constexpr auto operator""_MiB(ULL mebibytes) noexcept -> Size { return {mebibytes * static_cast<BT>(Unit_Val::MEBIBYTE)}; }
  inline constexpr auto operator""_GiB(ULL gibibytes) noexcept -> Size { return {gibibytes * static_cast<BT>(Unit_Val::GIBIBYTE)}; }
  inline constexpr auto operator""_TiB(ULL tebibytes) noexcept -> Size { return {tebibytes * static_cast<BT>(Unit_Val::TEBIBYTE)}; }
  inline constexpr auto operator""_PiB(ULL pebibytes) noexcept -> Size { return {pebibytes * static_cast<BT>(Unit_Val::PEBIBYTE)}; }
  inline constexpr auto operator""_EiB(ULL exbibytes) noexcept -> Size { return {exbibytes * static_cast<BT>(Unit_Val::EXBIBYTE)}; }
  inline constexpr auto operator""_ZiB(ULL zebibytes) noexcept -> Size { return {zebibytes * static_cast<BT>(Unit_Val::ZEBIBYTE)}; }
  inline constexpr auto operator""_YiB(ULL yobibytes) noexcept -> Size { return {yobibytes * static_cast<BT>(Unit_Val::YOBIBYTE)}; }
}; // namespace size::size_literals
