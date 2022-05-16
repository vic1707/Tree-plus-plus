#include "fs_utils.hpp"

namespace fs_utils {
  const std::array<std::string_view, 6> sizes = {"B", "KB", "MB", "GB", "TB", "PB"};

  SizeUnit::SizeUnit(size_t bytes) noexcept : bytes(bytes) {
    reload_unit();
  }
  void SizeUnit::reload_unit() {
    auto sizes_it = sizes.begin();
    size_t ratio_num = 1;
    for (size_t ratio_bytes = bytes; ratio_bytes > 1024; ratio_bytes /= 1024, ratio_num*=1024, ++sizes_it);
    unit = Unit{ 
      Ratio{ratio_num, 1}, 
      *sizes_it 
    };
  } 

  SizeUnit readable_dir_size(fs::directory_entry path) {
    size_t size = 0;
    for (fs::recursive_directory_iterator it(path); it != fs::recursive_directory_iterator(); ++it)
      if (!it->is_directory())
        size += fs::file_size(*it);
    return SizeUnit(size);
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
