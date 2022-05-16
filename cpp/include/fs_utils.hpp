#ifndef UTILS_HPP
  #define UTILS_HPP
  #include <array>
  #include <charconv>
  #include <filesystem>
  #include <iomanip>
  #include <ostream>
  #include <ratio>
  #include <string_view>
  #include <vector>

  namespace fs = std::filesystem;

  namespace fs_utils {
    
    struct Ratio {
      constexpr Ratio() noexcept : num(1), den(1) {}
      constexpr Ratio(std::uintmax_t num, std::uintmax_t den) noexcept : num(num), den(den) {}
      size_t num;
      size_t den;
      constexpr float operator*(size_t bytes) const noexcept {
        return static_cast<float>(bytes) *  static_cast<float>(den) / static_cast<float>(num);
      }
    };
    struct Unit
    {
      constexpr Unit() noexcept : ratio(), name("B") {}
      constexpr Unit(Ratio ratio, std::string_view name) noexcept : ratio(ratio), name(name) {}
      Ratio ratio;
      std::string_view name;
    };
    struct SizeUnit {
      SizeUnit() noexcept = default;
      SizeUnit(size_t bytes) noexcept;
      size_t bytes;
      Unit unit;
      constexpr float get_human_readable() const noexcept {
        return unit.ratio * bytes;
      }
      constexpr void operator+=(size_t b) noexcept {
        bytes += b;
        reload_unit();
      }
      void reload_unit();
    };

    inline std::ostream& operator<<(std::ostream &os, const fs_utils::SizeUnit &size_unit) {
      if (size_unit.unit.ratio.num == 1) {
        os << size_unit.bytes;
      } else {
        os << std::fixed << std::setprecision(2) << size_unit.get_human_readable();
      }
      os  << " " << size_unit.unit.name;
      return os;
    }

    SizeUnit readable_dir_size(fs::directory_entry path);
    std::vector<fs::directory_entry> list_files_first(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_files_of_dir(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_dirs_first(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_dirs_of_dir(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_entries_of_dir(fs::directory_entry dir, bool all_files);
  }
#endif
