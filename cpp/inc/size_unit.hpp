#ifndef SIZE_UNIT_HPP
  #define SIZE_UNIT_HPP
  /* std */
  #include <array>
  #include <ostream>
  #include <string_view>

  namespace SizeUnit {
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
      constexpr Unit(Ratio ratio, std::string_view name) noexcept : ratio(ratio), name(name) {}
    };

    struct SizeUnit {
      /* Members */
      size_t bytes;
      Unit unit;
      /* Constructors */
      constexpr SizeUnit() noexcept = default;
      constexpr SizeUnit(size_t bytes) noexcept : bytes(bytes) { reload_unit(); };
      /* Methods */
      constexpr float get_human_readable() const noexcept { return unit.ratio * bytes; }
      void reload_unit() noexcept;
      /* Operators */
      constexpr void operator+=(size_t b) noexcept {
        bytes += b;
        reload_unit();
      }

      friend inline constexpr std::ostream &operator<<(std::ostream &os, const SizeUnit &size_unit) noexcept {
        size_unit.unit.ratio.num == 1
          ? os << size_unit.bytes
          : os << ((double)(int)(size_unit.get_human_readable() * 100) / 100); // two decimal places
        os << " " << size_unit.unit.name;
        return os;
      }

      friend inline constexpr bool operator<(const SizeUnit &lhs, const SizeUnit &rhs) noexcept {
        return lhs.bytes < rhs.bytes;
      }
    };
  } // namespace SizeUnit
#endif // SIZE_UNIT_HPP
