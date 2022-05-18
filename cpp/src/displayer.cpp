#include "displayer.hpp"

// const std::array<std::string_view, 2> entry_pointers = { "├── ", "└── " };
// const std::array<std::string_view, 2> continuity_pointers = { "│   ", "    " };

void Classic::display(const Item &item, size_t tab) noexcept {
  for (size_t i = 0; i < tab; i++)
    std::cout.write("  ", 2);
  if (std::holds_alternative<FileDirInfos::DirInfos>(item)) {
    auto &dir = std::get<FileDirInfos::DirInfos>(item);
    display_info(&dir);
    for (auto &file : dir.items)
      display(file, tab + 1);
  } else {
    auto &file = std::get<FileDirInfos::FileInfos>(item);
    display_info(&file);
  }
}

void Classic::display_info(const FileDirInfos::ItemInfos *info) noexcept {
  char buff[20];
  std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&info->time));
  std::cout << info->path.filename().string() << " - " << info->size << " - " << buff << "\n";
}

// pour le tri la fct partition