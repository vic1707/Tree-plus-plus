#include "displayer.hpp"

// const std::array<std::string_view, 2> entry_pointers = { "├── ", "└── " };
// const std::array<std::string_view, 2> continuity_pointers = { "│   ", "    " };

void Classic::display(const Item& item, size_t tab) {
  for (size_t i = 0; i < tab; i++)
    std::cout.write("  ", 2);
  if (std::holds_alternative<FileDirInfos::DirInfos>(item)) {
    auto& dir = std::get<FileDirInfos::DirInfos>(item);
    display_info(&dir);
    for(auto& file : dir.items)
      display(file, tab + 1);
  } else {
    auto& file = std::get<FileDirInfos::FileInfos>(item);
    display_info(&file);
  }
}

void Classic::display_info(const FileDirInfos::ItemInfos* info) {
  char buf[64];
  auto tmval = std::localtime(&info->time);
  strftime(buf, sizeof buf, "%A %c", tmval);
  std::cout << info->path.filename().string() << " - " << info->size << " - " << buf << '\n';
}

// pour le tri la fct partition