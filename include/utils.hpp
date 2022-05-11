#ifndef UTILS_HPP
  #define UTILS_HPP
  #include <array>
  #include <charconv>
  #include <filesystem>
  #include <string_view>
  namespace fs = std::filesystem;

  namespace utils {
    extern const std::array<std::string_view, 6> sizes;

    struct size_unit {
      size_t size;
      const std::string_view* unit;
    };

    size_unit readable_file_size(size_t size_byte);
    size_unit readable_dir_size(fs::directory_entry path);
  }
#endif
