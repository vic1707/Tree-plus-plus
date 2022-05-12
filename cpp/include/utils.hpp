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
      float size;
      const std::string_view* unit;
    };

    size_unit readable_file_size(float size_byte);
    size_unit readable_dir_size(fs::directory_entry path);
  }
#endif
