#include "displayers/classic.hpp"

void Classic::display_file(const FileDirInfos::FileInfos *info, std::string prefix) noexcept {
  char buff[20];
  std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&info->time));
  std::cout << prefix << info->path.filename().string() << " - " << info->size << " - " << buff << "\n";
}

void Classic::display_folder(const FileDirInfos::DirInfos *info, std::string prefix) noexcept {
  std::cout << prefix << info->path.filename().string() << "\n";
}

void Classic::display(const Item &item, std::string prefix) noexcept {
  if (std::holds_alternative<FileDirInfos::DirInfos>(item)) { // Directory
    auto &dir = std::get<FileDirInfos::DirInfos>(item);
    display_folder(&dir, prefix);
    for (auto &child : dir.items)
      display(child, prefix + std::string(tab_size, ' '));
  } else {                                                    // File
    auto &file = std::get<FileDirInfos::FileInfos>(item);
    display_file(&file, prefix);
  }
}
