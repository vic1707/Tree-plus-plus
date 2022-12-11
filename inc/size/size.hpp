#pragma once
/* CUSTOM */
#include "size_enums.hpp"
/* STD */
#include <ostream>

namespace size {

  template <Base base = DEFAULT_BASE>
  class Size {
    private:
      BT m_bytes = 0;

    public:
      /* Nearest Unit Utils */
      [[nodiscard]] constexpr auto nearest_unit() const noexcept -> const Unit_Names& { return find_unit_pair(m_bytes, static_cast<int>(base)); }
      [[nodiscard]] constexpr auto nearest_unit(Base b) const noexcept -> const Unit_Names& { return find_unit_pair(m_bytes, static_cast<int>(b)); }

      /* Methods */
      [[nodiscard]] constexpr auto      bytes() const noexcept -> BT { return m_bytes; }
      [[nodiscard]] constexpr auto  kilobytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::KILOBYTE); }
      [[nodiscard]] constexpr auto  megabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::MEGABYTE); }
      [[nodiscard]] constexpr auto  gigabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::GIGABYTE); }
      [[nodiscard]] constexpr auto  terabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::TERABYTE); }
      [[nodiscard]] constexpr auto  petabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::PETABYTE); }
      [[nodiscard]] constexpr auto   exabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(  Unit::EXABYTE); }
      [[nodiscard]] constexpr auto zettabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::ZETTABYTE); }
      [[nodiscard]] constexpr auto yottabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::YOTTABYTE); }

      [[nodiscard]] constexpr auto kibibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::KIBIBYTE); }
      [[nodiscard]] constexpr auto mebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::MEBIBYTE); }
      [[nodiscard]] constexpr auto gibibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::GIBIBYTE); }
      [[nodiscard]] constexpr auto tebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::TEBIBYTE); }
      [[nodiscard]] constexpr auto pebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::PEBIBYTE); }
      [[nodiscard]] constexpr auto exbibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::EXBIBYTE); }
      [[nodiscard]] constexpr auto zebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::ZEBIBYTE); }
      [[nodiscard]] constexpr auto yobibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::YOBIBYTE); }

      /* Base conversion */
      [[nodiscard]] constexpr auto to_base2()  const noexcept -> Size<Base::Base2> requires (base == Base::Base10) { return Size<Base::Base2>(m_bytes); }
      [[nodiscard]] constexpr auto to_base10() const noexcept -> Size<Base::Base10> requires (base == Base::Base2) { return Size<Base::Base10>(m_bytes); }

      /* Constructors */
      [[nodiscard]] constexpr Size() noexcept = default;
      [[nodiscard]] constexpr Size(BT bytes) noexcept : m_bytes(bytes) {}
      [[nodiscard]] constexpr Size(std::integral auto bytes) noexcept : m_bytes(static_cast<BT>(bytes)) {}
      [[nodiscard]] constexpr Size(std::integral auto value, Unit unit) noexcept : m_bytes(static_cast<BT>(value * static_cast<BT>(unit))) {}
      [[nodiscard]] constexpr Size(const Size& other) noexcept = default;
      [[nodiscard]] constexpr Size(Size&& other) noexcept = default;

      /* Destructor */
      ~Size() noexcept = default;

      /* Operators Overloading */
      // comparison
      template<Base otherBase> [[nodiscard]] inline constexpr friend auto operator<=>(const Size& lhs, const Size<otherBase>& rhs) noexcept -> std::strong_ordering { return lhs.m_bytes <=> rhs.bytes(); }
      template<Base otherBase> [[nodiscard]] inline constexpr friend auto operator==(const Size& lhs, const Size<otherBase>& rhs) noexcept -> bool { return lhs.m_bytes == rhs.bytes(); }
      // arithmetic
      [[nodiscard]] inline constexpr friend auto operator+(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes + rhs.m_bytes; }
      [[nodiscard]] inline constexpr friend auto operator-(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes - rhs.m_bytes; }
      [[nodiscard]] inline constexpr friend auto operator*(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes * rhs.m_bytes; }
      [[nodiscard]] inline constexpr friend auto operator/(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes / rhs.m_bytes; }
      [[nodiscard]] inline constexpr friend auto operator%(const Size& lhs, const Size& rhs) noexcept -> Size { return lhs.m_bytes % rhs.m_bytes; }
      // copy assignment operators
      inline constexpr auto operator=(const Size& other) noexcept -> Size& = default;
      inline constexpr auto operator=(Size&& other) noexcept -> Size& = default;
      // compound assignment
      inline constexpr friend auto operator+=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes += rhs.m_bytes; return lhs; }
      inline constexpr friend auto operator-=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes -= rhs.m_bytes; return lhs; }
      inline constexpr friend auto operator*=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes *= rhs.m_bytes; return lhs; }
      inline constexpr friend auto operator/=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes /= rhs.m_bytes; return lhs; }
      inline constexpr friend auto operator%=(Size& lhs, const Size& rhs) noexcept -> Size& { lhs.m_bytes %= rhs.m_bytes; return lhs; }
      // prefix increment and decrement
      inline constexpr friend auto operator++(Size& size) noexcept -> Size& { ++size.m_bytes; return size; }
      inline constexpr friend auto operator--(Size& size) noexcept -> Size& { --size.m_bytes; return size; }
      // postfix increment and decrement
      inline constexpr friend auto operator++(Size& size, int) noexcept -> Size { ++size; return size; }
      inline constexpr friend auto operator--(Size& size, int) noexcept -> Size { --size; return size; }
      // shift bitwise
      [[nodiscard]] inline constexpr friend auto operator<<(const Size& size, const int shift) noexcept -> Size { return size.m_bytes << shift; }  // assert((std::numeric_limits<BT>::max() >> shift) > size.m_bytes);
      [[nodiscard]] inline constexpr friend auto operator>>(const Size& size, const int shift) noexcept -> Size { return size.m_bytes >> shift; }

      /* Formatting */
      friend std::ostream& operator<<(std::ostream& os, const Size& size) {
        const auto& [unit_base, unit_names] = size.nearest_unit();
        const auto ratio = static_cast<LD>(size.m_bytes) / static_cast<LD>(unit_base);

        return os << ratio
                  << " " << unit_names.at(static_cast<int>(CURRENT_STYLE))
                  << (ratio != 1 && (CURRENT_STYLE == Style::Long || CURRENT_STYLE == Style::LongLowercase) ? "s" : "");
      }
  }; // class Size

  template<Base base = DEFAULT_BASE>
  [[nodiscard]] static constexpr auto      from_bytes(std::integral auto      bytes) noexcept -> Size<base> { return bytes; }
  // base 10
  [[nodiscard]] static constexpr auto  from_kilobytes(std::integral auto  kilobytes) noexcept -> Size<Base::Base10> { return  kilobytes * static_cast<BT>( Unit::KILOBYTE); }
  [[nodiscard]] static constexpr auto  from_megabytes(std::integral auto  megabytes) noexcept -> Size<Base::Base10> { return  megabytes * static_cast<BT>( Unit::MEGABYTE); }
  [[nodiscard]] static constexpr auto  from_gigabytes(std::integral auto  gigabytes) noexcept -> Size<Base::Base10> { return  gigabytes * static_cast<BT>( Unit::GIGABYTE); }
  [[nodiscard]] static constexpr auto  from_terabytes(std::integral auto  terabytes) noexcept -> Size<Base::Base10> { return  terabytes * static_cast<BT>( Unit::TERABYTE); }
  [[nodiscard]] static constexpr auto  from_petabytes(std::integral auto  petabytes) noexcept -> Size<Base::Base10> { return  petabytes * static_cast<BT>( Unit::PETABYTE); }
  [[nodiscard]] static constexpr auto   from_exabytes(std::integral auto   exabytes) noexcept -> Size<Base::Base10> { return   exabytes * static_cast<BT>(  Unit::EXABYTE); }
  [[nodiscard]] static constexpr auto from_zettabytes(std::integral auto zettabytes) noexcept -> Size<Base::Base10> { return zettabytes * static_cast<BT>(Unit::ZETTABYTE); }
  [[nodiscard]] static constexpr auto from_yottabytes(std::integral auto yottabytes) noexcept -> Size<Base::Base10> { return yottabytes * static_cast<BT>(Unit::YOTTABYTE); }
  // base 2
  [[nodiscard]] static constexpr auto from_kibibytes(std::integral auto kibibytes) noexcept -> Size<Base::Base2> { return kibibytes * static_cast<BT>(Unit::KIBIBYTE); }
  [[nodiscard]] static constexpr auto from_mebibytes(std::integral auto mebibytes) noexcept -> Size<Base::Base2> { return mebibytes * static_cast<BT>(Unit::MEBIBYTE); }
  [[nodiscard]] static constexpr auto from_gibibytes(std::integral auto gibibytes) noexcept -> Size<Base::Base2> { return gibibytes * static_cast<BT>(Unit::GIBIBYTE); }
  [[nodiscard]] static constexpr auto from_tebibytes(std::integral auto tebibytes) noexcept -> Size<Base::Base2> { return tebibytes * static_cast<BT>(Unit::TEBIBYTE); }
  [[nodiscard]] static constexpr auto from_pebibytes(std::integral auto pebibytes) noexcept -> Size<Base::Base2> { return pebibytes * static_cast<BT>(Unit::PEBIBYTE); }
  [[nodiscard]] static constexpr auto from_exbibytes(std::integral auto exbibytes) noexcept -> Size<Base::Base2> { return exbibytes * static_cast<BT>(Unit::EXBIBYTE); }
  [[nodiscard]] static constexpr auto from_zebibytes(std::integral auto zebibytes) noexcept -> Size<Base::Base2> { return zebibytes * static_cast<BT>(Unit::ZEBIBYTE); }
  [[nodiscard]] static constexpr auto from_yobibytes(std::integral auto yobibytes) noexcept -> Size<Base::Base2> { return yobibytes * static_cast<BT>(Unit::YOBIBYTE); }
}; // namespace size

using ULL = unsigned long long;
namespace size::size_literals {
  inline constexpr auto operator""_B (ULL      bytes) noexcept -> Size<DEFAULT_BASE> { return {bytes}; }
  // Base-10 units
  inline constexpr auto operator""_KB(ULL  kilobytes) noexcept -> Size<Base::Base10> { return { kilobytes *  static_cast<BT>(Unit::KILOBYTE)}; }
  inline constexpr auto operator""_MB(ULL  megabytes) noexcept -> Size<Base::Base10> { return { megabytes *  static_cast<BT>(Unit::MEGABYTE)}; }
  inline constexpr auto operator""_GB(ULL  gigabytes) noexcept -> Size<Base::Base10> { return { gigabytes *  static_cast<BT>(Unit::GIGABYTE)}; }
  inline constexpr auto operator""_TB(ULL  terabytes) noexcept -> Size<Base::Base10> { return { terabytes *  static_cast<BT>(Unit::TERABYTE)}; }
  inline constexpr auto operator""_PB(ULL  petabytes) noexcept -> Size<Base::Base10> { return { petabytes *  static_cast<BT>(Unit::PETABYTE)}; }
  inline constexpr auto operator""_EB(ULL   exabytes) noexcept -> Size<Base::Base10> { return {  exabytes *   static_cast<BT>(Unit::EXABYTE)}; }
  inline constexpr auto operator""_ZB(ULL zettabytes) noexcept -> Size<Base::Base10> { return {zettabytes * static_cast<BT>(Unit::ZETTABYTE)}; }
  inline constexpr auto operator""_YB(ULL yottabytes) noexcept -> Size<Base::Base10> { return {yottabytes * static_cast<BT>(Unit::YOTTABYTE)}; }
  // Base-2 units
  inline constexpr auto operator""_KiB(ULL kibibytes) noexcept -> Size<Base::Base2> { return {kibibytes * static_cast<BT>(Unit::KIBIBYTE)}; }
  inline constexpr auto operator""_MiB(ULL mebibytes) noexcept -> Size<Base::Base2> { return {mebibytes * static_cast<BT>(Unit::MEBIBYTE)}; }
  inline constexpr auto operator""_GiB(ULL gibibytes) noexcept -> Size<Base::Base2> { return {gibibytes * static_cast<BT>(Unit::GIBIBYTE)}; }
  inline constexpr auto operator""_TiB(ULL tebibytes) noexcept -> Size<Base::Base2> { return {tebibytes * static_cast<BT>(Unit::TEBIBYTE)}; }
  inline constexpr auto operator""_PiB(ULL pebibytes) noexcept -> Size<Base::Base2> { return {pebibytes * static_cast<BT>(Unit::PEBIBYTE)}; }
  inline constexpr auto operator""_EiB(ULL exbibytes) noexcept -> Size<Base::Base2> { return {exbibytes * static_cast<BT>(Unit::EXBIBYTE)}; }
  inline constexpr auto operator""_ZiB(ULL zebibytes) noexcept -> Size<Base::Base2> { return {zebibytes * static_cast<BT>(Unit::ZEBIBYTE)}; }
  inline constexpr auto operator""_YiB(ULL yobibytes) noexcept -> Size<Base::Base2> { return {yobibytes * static_cast<BT>(Unit::YOBIBYTE)}; }
}; // namespace size::size_literals
