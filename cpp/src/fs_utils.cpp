#include "fs_utils.hpp"

namespace fs_utils {
  const std::array<std::string_view, 6> sizes = {"B", "KB", "MB", "GB", "TB", "PB"};

  size_unit readable_file_size(double size_byte) {
    size_t index = 0;
    for (; size_byte > 1024.0; size_byte /= 1024.0, index++);
    return {((double)(int)(size_byte * 100)/100), &sizes[index]}; // two digits after decimal point
  }

  size_unit readable_dir_size(fs::directory_entry path) {
    size_t size = 0;
    for (fs::recursive_directory_iterator it(path); it != fs::recursive_directory_iterator(); ++it)
      if (!fs::is_directory(*it))
        size += fs::file_size(*it);
    return readable_file_size((double) size);
  }

  std::vector<fs::directory_entry> list_files_of_dir(fs::directory_entry dir, bool all_files) {
    std::vector<fs::directory_entry> entries;
    for (const fs::directory_entry &entry : fs::directory_iterator(dir))
      if (entry.is_regular_file() && (all_files || !entry.path().filename().string().starts_with(".")))
        entries.push_back(entry);
    
    sort(entries.begin(), entries.end(), [](const fs::directory_entry &left, const fs::directory_entry &right) -> bool {
      return left.path().filename() < right.path().filename();
    });

    return entries;
  }

  std::vector<fs::directory_entry> list_dirs_of_dir(fs::directory_entry dir, bool all_files) {
    std::vector<fs::directory_entry> entries;
    for (const fs::directory_entry &entry : fs::directory_iterator(dir))
      if (entry.is_directory() && (all_files || !entry.path().filename().string().starts_with(".")))
        entries.push_back(entry);

    sort(entries.begin(), entries.end(), [](const fs::directory_entry &left, const fs::directory_entry &right) -> bool {
      return left.path().filename() < right.path().filename();
    });

    return entries;
  }

  std::vector<fs::directory_entry> list_dirs_first(fs::directory_entry dir, bool all_files) {
    std::vector<fs::directory_entry> entries = list_dirs_of_dir(dir, all_files);
    std::vector<fs::directory_entry> files = list_files_of_dir(dir, all_files);
    entries.insert(entries.end(), files.begin(), files.end());
    return entries;
  }

  std::vector<fs::directory_entry> list_files_first(fs::directory_entry dir, bool all_files) {
    std::vector<fs::directory_entry> entries = list_files_of_dir(dir, all_files);
    std::vector<fs::directory_entry> dirs = list_dirs_of_dir(dir, all_files);
    entries.insert(entries.end(), dirs.begin(), dirs.end());
    return entries;
  }
    

  std::vector<fs::directory_entry> list_entries_of_dir(fs::directory_entry dir, bool all_files) {
    std::vector<fs::directory_entry> entries;
    for (const fs::directory_entry &entry : fs::directory_iterator(dir))
      if(all_files || !entry.path().filename().string().starts_with("."))
        entries.push_back(entry);

    sort(entries.begin(), entries.end(), [](const fs::directory_entry &left, const fs::directory_entry &right) -> bool {
      return left.path().filename() < right.path().filename();
    });

    return entries;
  }
}
