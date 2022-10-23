#pragma once
/* CUSTOM */
#include "base.hpp"
#include "style.hpp"
#include "unit.hpp"
/* STD */
#include <array>
#include <concepts>
#include <ostream>
#include <string_view>

namespace size {
  class Size {
    private:
      BT m_bytes = 0;
      static Base m_base;
      static Style m_style;

    public:
      /* static base */
      static auto get_base() noexcept -> Base { return m_base; }
      static constexpr void set_base(Base base) noexcept { m_base = base; }
      /* static style */
      static auto get_style() noexcept -> Style { return m_style; }
      static constexpr void set_style(Style style) noexcept { m_style = style; }

      /* Methods */
      [[nodiscard]] constexpr auto      bytes() const noexcept -> BT { return m_bytes; }
      [[nodiscard]] constexpr auto  kilobytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit_Val::KILOBYTE); }
      [[nodiscard]] constexpr auto  megabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit_Val::MEGABYTE); }
      [[nodiscard]] constexpr auto  gigabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit_Val::GIGABYTE); }
      [[nodiscard]] constexpr auto  terabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit_Val::TERABYTE); }
      [[nodiscard]] constexpr auto  petabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit_Val::PETABYTE); }
      [[nodiscard]] constexpr auto   exabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(  Unit_Val::EXABYTE); }
      [[nodiscard]] constexpr auto zettabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::ZETTABYTE); }
      [[nodiscard]] constexpr auto yottabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::YOTTABYTE); }

      [[nodiscard]] constexpr auto kibibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::KIBIBYTE); }
      [[nodiscard]] constexpr auto mebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::MEBIBYTE); }
      [[nodiscard]] constexpr auto gibibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::GIBIBYTE); }
      [[nodiscard]] constexpr auto tebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::TEBIBYTE); }
      [[nodiscard]] constexpr auto pebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::PEBIBYTE); }
      [[nodiscard]] constexpr auto exbibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::EXBIBYTE); }
      [[nodiscard]] constexpr auto zebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::ZEBIBYTE); }
      [[nodiscard]] constexpr auto yobibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit_Val::YOBIBYTE); }

      /* Constructors */
      [[nodiscard]] constexpr Size() noexcept = default;
      [[nodiscard]] constexpr Size(BT bytes) noexcept : m_bytes(bytes) {}
      [[nodiscard]] constexpr Size(std::integral auto bytes) noexcept : m_bytes(static_cast<BT>(bytes)) {}
      [[nodiscard]] constexpr Size(std::integral auto value, Unit_Val unit) noexcept : m_bytes(static_cast<BT>(value * static_cast<BT>(unit))) {}
      [[nodiscard]] constexpr Size(const Size& other) noexcept = default;
      [[nodiscard]] constexpr Size(Size&& other) noexcept = default;
      // base 10
      [[nodiscard]] static constexpr auto      from_bytes(std::integral auto  bytes)     noexcept -> Size { return bytes; }
      [[nodiscard]] static constexpr auto  from_kilobytes(std::integral auto  kilobytes) noexcept -> Size { return  kilobytes * static_cast<BT>( Unit_Val::KILOBYTE); }
      [[nodiscard]] static constexpr auto  from_megabytes(std::integral auto  megabytes) noexcept -> Size { return  megabytes * static_cast<BT>( Unit_Val::MEGABYTE); }
      [[nodiscard]] static constexpr auto  from_gigabytes(std::integral auto  gigabytes) noexcept -> Size { return  gigabytes * static_cast<BT>( Unit_Val::GIGABYTE); }
      [[nodiscard]] static constexpr auto  from_terabytes(std::integral auto  terabytes) noexcept -> Size { return  terabytes * static_cast<BT>( Unit_Val::TERABYTE); }
      [[nodiscard]] static constexpr auto  from_petabytes(std::integral auto  petabytes) noexcept -> Size { return  petabytes * static_cast<BT>( Unit_Val::PETABYTE); }
      [[nodiscard]] static constexpr auto   from_exabytes(std::integral auto   exabytes) noexcept -> Size { return   exabytes *  static_cast<BT>( Unit_Val::EXABYTE); }
      [[nodiscard]] static constexpr auto from_zettabytes(std::integral auto zettabytes) noexcept -> Size { return zettabytes * static_cast<BT>(Unit_Val::ZETTABYTE); }
      [[nodiscard]] static constexpr auto from_yottabytes(std::integral auto yottabytes) noexcept -> Size { return yottabytes * static_cast<BT>(Unit_Val::YOTTABYTE); }
      // base 2
      [[nodiscard]] static constexpr auto from_kibibytes(std::integral auto kibibytes) noexcept -> Size { return kibibytes * static_cast<BT>(Unit_Val::KIBIBYTE); }
      [[nodiscard]] static constexpr auto from_mebibytes(std::integral auto mebibytes) noexcept -> Size { return mebibytes * static_cast<BT>(Unit_Val::MEBIBYTE); }
      [[nodiscard]] static constexpr auto from_gibibytes(std::integral auto gibibytes) noexcept -> Size { return gibibytes * static_cast<BT>(Unit_Val::GIBIBYTE); }
      [[nodiscard]] static constexpr auto from_tebibytes(std::integral auto tebibytes) noexcept -> Size { return tebibytes * static_cast<BT>(Unit_Val::TEBIBYTE); }
      [[nodiscard]] static constexpr auto from_pebibytes(std::integral auto pebibytes) noexcept -> Size { return pebibytes * static_cast<BT>(Unit_Val::PEBIBYTE); }
      [[nodiscard]] static constexpr auto from_exbibytes(std::integral auto exbibytes) noexcept -> Size { return exbibytes * static_cast<BT>(Unit_Val::EXBIBYTE); }
      [[nodiscard]] static constexpr auto from_zebibytes(std::integral auto zebibytes) noexcept -> Size { return zebibytes * static_cast<BT>(Unit_Val::ZEBIBYTE); }
      [[nodiscard]] static constexpr auto from_yobibytes(std::integral auto yobibytes) noexcept -> Size { return yobibytes * static_cast<BT>(Unit_Val::YOBIBYTE); }

      /* Operators Overloading */
      // comparison
      [[nodiscard]] inline friend auto operator<=>(const Size& lhs, const Size& rhs) noexcept -> std::strong_ordering { return lhs.m_bytes <=> rhs.m_bytes; }
      [[nodiscard]] inline friend auto operator==(const Size& lhs, const Size& rhs) noexcept -> bool { return lhs.m_bytes == rhs.m_bytes; }
      // arithmetic
      [[nodiscard]] inline friend auto operator+(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes + rhs.m_bytes; }
      [[nodiscard]] inline friend auto operator-(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes - rhs.m_bytes; }
      [[nodiscard]] inline friend auto operator*(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes * rhs.m_bytes; }
      [[nodiscard]] inline friend auto operator/(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes / rhs.m_bytes; }
      [[nodiscard]] inline friend auto operator%(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes % rhs.m_bytes; }
      // compound assignment
      inline friend auto operator+=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes += rhs.m_bytes; return lhs; }
      inline friend auto operator-=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes -= rhs.m_bytes; return lhs; }
      inline friend auto operator*=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes *= rhs.m_bytes; return lhs; }
      inline friend auto operator/=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes /= rhs.m_bytes; return lhs; }
      inline friend auto operator%=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes %= rhs.m_bytes; return lhs; }
      // prefix increment and decrement
      inline friend auto operator++(Size& size) noexcept -> Size& { ++size.m_bytes; return size; }
      inline friend auto operator--(Size& size) noexcept -> Size& { --size.m_bytes; return size; }
      // postfix increment and decrement
      inline friend auto operator++(Size& size, int) noexcept -> Size { ++size; return size; }
      inline friend auto operator--(Size& size, int) noexcept -> Size { --size; return size; }
      // shift bitwise
      [[nodiscard]] inline friend auto operator<<(const Size& size, const int shift) noexcept -> Size { return size.m_bytes << shift; }  // assert((std::numeric_limits<BT>::max() >> shift) > size.m_bytes);
      [[nodiscard]] inline friend auto operator>>(const Size& size, const int shift) noexcept -> Size { return size.m_bytes >> shift; }

      /* Formatting */
      friend std::ostream& operator<<(std::ostream& os, const Size& size) {
        const auto& unit = get_unit(size.m_bytes, static_cast<int>(m_base));

        return os << static_cast<LD>(size.m_bytes) / static_cast<LD>(unit.value)
                  << " " << unit.names.at(static_cast<int>(m_style))
                  << (static_cast<int>(m_style) > 1 && size.m_bytes != 1 ? "s" : "");
      }
  }; // class Size
}; // namespace size
