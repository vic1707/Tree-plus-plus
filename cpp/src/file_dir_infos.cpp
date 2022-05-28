#include "file_dir_infos.hpp"

namespace FileDirInfos {
  template <typename Item>
  inline void DirInfos::push_item(const fs::directory_entry &entry) noexcept {
    Item item(entry);
    size += item.size.bytes;
    items.emplace_back(std::move(item));
  }

  ItemInfos::ItemInfos(const fs::directory_entry &entry) noexcept {
    path = entry.path();
    size = entry.is_directory() ? SizeUnit::SizeUnit() : fs::file_size(path);
    time = Utils::to_time_t(fs::last_write_time(path));
    name = NameInfos(path);
  }

  DirInfos::DirInfos(const fs::directory_entry &entry) noexcept : ItemInfos(entry) {
    for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it)
      it->is_directory()
        ? push_item<DirInfos>(*it)
        : push_item<FileInfos>(*it);
  }
} // namespace FileDirInfos
