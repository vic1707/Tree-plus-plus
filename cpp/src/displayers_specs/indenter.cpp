#include "displayers_specs/indenter.hpp"

void Indenter::display(const FileDirInfos::DirInfos &directory, std::string prefix) noexcept {
  for (auto &child : directory.items) {
    const auto entry_p = &child == &directory.items.back() ? last_entry_pointer : entry_pointer;
    const auto continuity_p = &child == &directory.items.back() ? last_continuity_indent : continuity_indent;
    if (std::holds_alternative<FileDirInfos::DirInfos>(child)) {  // Directory
      auto &dir = std::get<FileDirInfos::DirInfos>(child);
      display_folder(&dir, prefix + entry_p);
      display(dir, prefix + continuity_p);
    } else {                                                      // File
      auto &file = std::get<FileDirInfos::FileInfos>(child);
      display_file(&file, prefix + entry_p);
    }
  }
}
