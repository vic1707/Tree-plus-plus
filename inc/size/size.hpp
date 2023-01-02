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
      [[nodiscard]] constexpr auto       bytes() const noexcept -> BT { return m_bytes; }
      [[nodiscard]] constexpr auto   kilobytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(  Unit::KILOBYTE); }
      [[nodiscard]] constexpr auto   megabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(  Unit::MEGABYTE); }
      [[nodiscard]] constexpr auto   gigabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(  Unit::GIGABYTE); }
      [[nodiscard]] constexpr auto   terabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(  Unit::TERABYTE); }
      [[nodiscard]] constexpr auto   petabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(  Unit::PETABYTE); }
      [[nodiscard]] constexpr auto    exabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(   Unit::EXABYTE); }
      [[nodiscard]] constexpr auto  zettabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::ZETTABYTE); }
      [[nodiscard]] constexpr auto  yottabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::YOTTABYTE); }
      [[nodiscard]] constexpr auto  ronnabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::RONNABYTE); }
      [[nodiscard]] constexpr auto quettabytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::QUETTABYTE); }

      [[nodiscard]] constexpr auto  kibibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::KIBIBYTE); }
      [[nodiscard]] constexpr auto  mebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::MEBIBYTE); }
      [[nodiscard]] constexpr auto  gibibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::GIBIBYTE); }
      [[nodiscard]] constexpr auto  tebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::TEBIBYTE); }
      [[nodiscard]] constexpr auto  pebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::PEBIBYTE); }
      [[nodiscard]] constexpr auto  exbibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::EXBIBYTE); }
      [[nodiscard]] constexpr auto  zebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::ZEBIBYTE); }
      [[nodiscard]] constexpr auto  yobibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::YOBIBYTE); }
      [[nodiscard]] constexpr auto  robibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>( Unit::ROBIBYTE); }
      [[nodiscard]] constexpr auto quebibytes() const noexcept -> LD { return static_cast<LD>(m_bytes) / static_cast<LD>(Unit::QUEBIBYTE); }

      /* Base conversion */
      [[nodiscard]] constexpr auto to_base2() const noexcept -> Size<Base::Base2> requires (base == Base::Base10) { return Size<Base::Base2>(m_bytes); }
      [[nodiscard]] constexpr auto to_base10() const noexcept -> Size<Base::Base10> requires (base == Base::Base2) { return Size<Base::Base10>(m_bytes); }
      template<Base b> [[nodiscard]] constexpr auto to_base() const noexcept -> Size<b> { return Size<b>(m_bytes); }

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
      // comparison with other bases
      template<Base otherBase> [[nodiscard]] constexpr auto operator<=>(const Size<otherBase>& rhs) const noexcept -> std::strong_ordering { return m_bytes <=> rhs.bytes(); }
      template<Base otherBase> [[nodiscard]] constexpr auto operator==(const Size<otherBase>& rhs) const noexcept -> bool { return m_bytes == rhs.bytes(); }
      // comparison with integral types
      [[nodiscard]] constexpr auto operator<=>(const std::integral auto& rhs) const noexcept -> std::strong_ordering { return m_bytes <=> static_cast<BT>(rhs); }
      [[nodiscard]] constexpr auto operator==(const std::integral auto& rhs) const noexcept -> bool { return m_bytes == static_cast<BT>(rhs); }
      // comparison with BT type (not supported by std::integral)
      [[nodiscard]] constexpr auto operator<=>(const BT& rhs) const noexcept -> std::strong_ordering { return m_bytes <=> rhs; }
      [[nodiscard]] constexpr auto operator==(const BT& rhs) const noexcept -> bool { return m_bytes == rhs; }
      // arithmetic
      [[nodiscard]] constexpr auto operator+(const Size& rhs) const noexcept -> Size { return m_bytes + rhs.m_bytes; }
      [[nodiscard]] constexpr auto operator-(const Size& rhs) const noexcept -> Size { return m_bytes - rhs.m_bytes; }
      [[nodiscard]] constexpr auto operator*(const Size& rhs) const noexcept -> Size { return m_bytes * rhs.m_bytes; }
      [[nodiscard]] constexpr auto operator/(const Size& rhs) const noexcept -> Size { return m_bytes / rhs.m_bytes; }
      [[nodiscard]] constexpr auto operator%(const Size& rhs) const noexcept -> Size { return m_bytes % rhs.m_bytes; }
      // copy assignment operators
      [[nodiscard]] constexpr auto operator=(const Size& other) noexcept -> Size& = default;
      [[nodiscard]] constexpr auto operator=(Size&& other) noexcept -> Size& = default;
      // compound assignment
      constexpr auto operator+=(const Size& rhs) noexcept -> Size& { m_bytes += rhs.m_bytes; return *this; }
      constexpr auto operator-=(const Size& rhs) noexcept -> Size& { m_bytes -= rhs.m_bytes; return *this; }
      constexpr auto operator*=(const Size& rhs) noexcept -> Size& { m_bytes *= rhs.m_bytes; return *this; }
      constexpr auto operator/=(const Size& rhs) noexcept -> Size& { m_bytes /= rhs.m_bytes; return *this; }
      constexpr auto operator%=(const Size& rhs) noexcept -> Size& { m_bytes %= rhs.m_bytes; return *this; }
      // prefix increment and decrement
      [[nodiscard]] constexpr auto operator++() noexcept -> Size& { ++m_bytes; return *this; }
      [[nodiscard]] constexpr auto operator--() noexcept -> Size& { --m_bytes; return *this; }
      // postfix increment and decrement
      [[nodiscard]] constexpr auto operator++(int) noexcept -> Size { auto old = *this; ++m_bytes; return old; }
      [[nodiscard]] constexpr auto operator--(int) noexcept -> Size { auto old = *this; --m_bytes; return old; }
      // shift bitwise
      [[nodiscard]] constexpr auto operator<<(const int shift) const noexcept -> Size { return m_bytes << shift; }  // assert((std::numeric_limits<BT>::max() >> shift) > size.m_bytes);
      [[nodiscard]] constexpr auto operator>>(const int shift) const noexcept -> Size { return m_bytes >> shift; }  // assert((std::numeric_limits<BT>::max() << shift) > size.m_bytes);
  }; // class Size
  
  /* Formatting */
  template<Base base>
  std::ostream& operator<<(std::ostream& os, const Size<base>& size) {
    const auto& [unit_base, unit_names] = size.nearest_unit();
    const auto ratio = static_cast<LD>(size.bytes()) / static_cast<LD>(unit_base);

    return os << ratio
              << " " << unit_names.at(static_cast<int>(CURRENT_STYLE))
              << (ratio != 1 && (CURRENT_STYLE == Style::Long || CURRENT_STYLE == Style::LongLowercase) ? "s" : "");
  }

  template<Base base = DEFAULT_BASE>
  [[nodiscard]] constexpr auto       from_bytes(std::integral auto       bytes) noexcept -> Size<base> { return bytes; }
  // base 10
  [[nodiscard]] constexpr auto   from_kilobytes(std::integral auto   kilobytes) noexcept -> Size<Base::Base10> { return   kilobytes * static_cast<BT>(  Unit::KILOBYTE); }
  [[nodiscard]] constexpr auto   from_megabytes(std::integral auto   megabytes) noexcept -> Size<Base::Base10> { return   megabytes * static_cast<BT>(  Unit::MEGABYTE); }
  [[nodiscard]] constexpr auto   from_gigabytes(std::integral auto   gigabytes) noexcept -> Size<Base::Base10> { return   gigabytes * static_cast<BT>(  Unit::GIGABYTE); }
  [[nodiscard]] constexpr auto   from_terabytes(std::integral auto   terabytes) noexcept -> Size<Base::Base10> { return   terabytes * static_cast<BT>(  Unit::TERABYTE); }
  [[nodiscard]] constexpr auto   from_petabytes(std::integral auto   petabytes) noexcept -> Size<Base::Base10> { return   petabytes * static_cast<BT>(  Unit::PETABYTE); }
  [[nodiscard]] constexpr auto    from_exabytes(std::integral auto    exabytes) noexcept -> Size<Base::Base10> { return    exabytes * static_cast<BT>(   Unit::EXABYTE); }
  [[nodiscard]] constexpr auto  from_zettabytes(std::integral auto  zettabytes) noexcept -> Size<Base::Base10> { return  zettabytes * static_cast<BT>( Unit::ZETTABYTE); }
  [[nodiscard]] constexpr auto  from_yottabytes(std::integral auto  yottabytes) noexcept -> Size<Base::Base10> { return  yottabytes * static_cast<BT>( Unit::YOTTABYTE); }
  [[nodiscard]] constexpr auto  from_ronnabytes(std::integral auto  ronnabytes) noexcept -> Size<Base::Base10> { return  ronnabytes * static_cast<BT>( Unit::RONNABYTE); }
  [[nodiscard]] constexpr auto from_quettabytes(std::integral auto quettabytes) noexcept -> Size<Base::Base10> { return quettabytes * static_cast<BT>(Unit::QUETTABYTE); }
  // base 2
  [[nodiscard]] constexpr auto  from_kibibytes(std::integral auto  kibibytes) noexcept -> Size<Base::Base2> { return  kibibytes * static_cast<BT>( Unit::KIBIBYTE); }
  [[nodiscard]] constexpr auto  from_mebibytes(std::integral auto  mebibytes) noexcept -> Size<Base::Base2> { return  mebibytes * static_cast<BT>( Unit::MEBIBYTE); }
  [[nodiscard]] constexpr auto  from_gibibytes(std::integral auto  gibibytes) noexcept -> Size<Base::Base2> { return  gibibytes * static_cast<BT>( Unit::GIBIBYTE); }
  [[nodiscard]] constexpr auto  from_tebibytes(std::integral auto  tebibytes) noexcept -> Size<Base::Base2> { return  tebibytes * static_cast<BT>( Unit::TEBIBYTE); }
  [[nodiscard]] constexpr auto  from_pebibytes(std::integral auto  pebibytes) noexcept -> Size<Base::Base2> { return  pebibytes * static_cast<BT>( Unit::PEBIBYTE); }
  [[nodiscard]] constexpr auto  from_exbibytes(std::integral auto  exbibytes) noexcept -> Size<Base::Base2> { return  exbibytes * static_cast<BT>( Unit::EXBIBYTE); }
  [[nodiscard]] constexpr auto  from_zebibytes(std::integral auto  zebibytes) noexcept -> Size<Base::Base2> { return  zebibytes * static_cast<BT>( Unit::ZEBIBYTE); }
  [[nodiscard]] constexpr auto  from_yobibytes(std::integral auto  yobibytes) noexcept -> Size<Base::Base2> { return  yobibytes * static_cast<BT>( Unit::YOBIBYTE); }
  [[nodiscard]] constexpr auto  from_robibytes(std::integral auto  robibytes) noexcept -> Size<Base::Base2> { return  robibytes * static_cast<BT>( Unit::ROBIBYTE); }
  [[nodiscard]] constexpr auto from_quebibytes(std::integral auto quebibytes) noexcept -> Size<Base::Base2> { return quebibytes * static_cast<BT>(Unit::QUEBIBYTE); }
}; // namespace size

using ULL = unsigned long long;
namespace size::size_literals {
  [[nodiscard]] constexpr auto operator""_B (ULL       bytes) noexcept -> Size<DEFAULT_BASE> { return {bytes}; }
  // Base-10 units
  [[nodiscard]] constexpr auto operator""_KB(ULL   kilobytes) noexcept -> Size<Base::Base10> { return {  kilobytes *  static_cast<BT>( Unit::KILOBYTE)}; }
  [[nodiscard]] constexpr auto operator""_MB(ULL   megabytes) noexcept -> Size<Base::Base10> { return {  megabytes *  static_cast<BT>( Unit::MEGABYTE)}; }
  [[nodiscard]] constexpr auto operator""_GB(ULL   gigabytes) noexcept -> Size<Base::Base10> { return {  gigabytes *  static_cast<BT>( Unit::GIGABYTE)}; }
  [[nodiscard]] constexpr auto operator""_TB(ULL   terabytes) noexcept -> Size<Base::Base10> { return {  terabytes *  static_cast<BT>( Unit::TERABYTE)}; }
  [[nodiscard]] constexpr auto operator""_PB(ULL   petabytes) noexcept -> Size<Base::Base10> { return {  petabytes *  static_cast<BT>( Unit::PETABYTE)}; }
  [[nodiscard]] constexpr auto operator""_EB(ULL    exabytes) noexcept -> Size<Base::Base10> { return {   exabytes *   static_cast<BT>( Unit::EXABYTE)}; }
  [[nodiscard]] constexpr auto operator""_ZB(ULL  zettabytes) noexcept -> Size<Base::Base10> { return { zettabytes * static_cast<BT>( Unit::ZETTABYTE)}; }
  [[nodiscard]] constexpr auto operator""_YB(ULL  yottabytes) noexcept -> Size<Base::Base10> { return { yottabytes * static_cast<BT>( Unit::YOTTABYTE)}; }
  [[nodiscard]] constexpr auto operator""_RB(ULL  ronnabytes) noexcept -> Size<Base::Base10> { return { ronnabytes * static_cast<BT>( Unit::RONNABYTE)}; }
  [[nodiscard]] constexpr auto operator""_QB(ULL quettabytes) noexcept -> Size<Base::Base10> { return {quettabytes * static_cast<BT>(Unit::QUETTABYTE)}; }
  // Base-2 units
  [[nodiscard]] constexpr auto operator""_KiB(ULL  kibibytes) noexcept -> Size<Base::Base2> { return { kibibytes * static_cast<BT>( Unit::KIBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_MiB(ULL  mebibytes) noexcept -> Size<Base::Base2> { return { mebibytes * static_cast<BT>( Unit::MEBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_GiB(ULL  gibibytes) noexcept -> Size<Base::Base2> { return { gibibytes * static_cast<BT>( Unit::GIBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_TiB(ULL  tebibytes) noexcept -> Size<Base::Base2> { return { tebibytes * static_cast<BT>( Unit::TEBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_PiB(ULL  pebibytes) noexcept -> Size<Base::Base2> { return { pebibytes * static_cast<BT>( Unit::PEBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_EiB(ULL  exbibytes) noexcept -> Size<Base::Base2> { return { exbibytes * static_cast<BT>( Unit::EXBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_ZiB(ULL  zebibytes) noexcept -> Size<Base::Base2> { return { zebibytes * static_cast<BT>( Unit::ZEBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_YiB(ULL  yobibytes) noexcept -> Size<Base::Base2> { return { yobibytes * static_cast<BT>( Unit::YOBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_RiB(ULL  robibytes) noexcept -> Size<Base::Base2> { return { robibytes * static_cast<BT>( Unit::ROBIBYTE)}; }
  [[nodiscard]] constexpr auto operator""_QiB(ULL quebibytes) noexcept -> Size<Base::Base2> { return {quebibytes * static_cast<BT>(Unit::QUEBIBYTE)}; }
}; // namespace size::size_literals
