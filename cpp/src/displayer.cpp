#include "displayer.hpp"

const std::array<std::string_view, 2> entry_pointers = { "├── ", "└── " };
const std::array<std::string_view, 2> continuity_pointers = { "│   ", "    " };

void Classic::display_file(const FileDirInfos::FileInfos *info) noexcept {
  char buff[20];
  std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&info->time));
  std::cout << info->path.filename().string() << " - " << info->size << " - " << buff << "\n";
}

void Classic::display_folder(const FileDirInfos::DirInfos *info) noexcept {
  std::cout << info->path.filename().string() << "\n";
}

void Classic::display(const Item &item) noexcept {
  if (std::holds_alternative<FileDirInfos::DirInfos>(item)) { // Directory
    auto &dir = std::get<FileDirInfos::DirInfos>(item);
    display_folder(&dir);
    for (auto &child : dir.items)
      display(child);
  } else {                                                    // File
    auto &file = std::get<FileDirInfos::FileInfos>(item);
    display_file(&file);
  }
}

// pour le tri la fct partition
