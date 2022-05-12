#ifndef UTILS_HPP
  #define UTILS_HPP
  #include <array>
  #include <charconv>
  #include <filesystem>
  #include <string_view>
  #include <vector>

  namespace fs = std::filesystem;

  namespace utils {
    extern const std::array<std::string_view, 6> sizes;

    struct size_unit {
      float size;
      const std::string_view* unit;
    };

    size_unit readable_file_size(float size_byte);
    size_unit readable_dir_size(fs::directory_entry path);
    std::vector<fs::directory_entry> list_files_first(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_files_of_dir(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_dirs_first(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_dirs_of_dir(fs::directory_entry dir, bool all_files);
    std::vector<fs::directory_entry> list_entries_of_dir(fs::directory_entry dir, bool all_files);
  }
#endif
