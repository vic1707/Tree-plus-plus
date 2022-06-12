#include "file_dir_infos.hpp"

namespace FileDirInfos {
  template <typename Item>
  inline void DirInfos::push_item(fs::directory_entry entry, bool hidden) {
    if (!hidden && entry.path().filename().string().front() == '.') return;
    Item item;
    if constexpr (std::is_same_v<Item, DirInfos>) {
      item = DirInfos(entry, hidden);
      ++children.local.dirs;
      children.total.dirs += item.children.total.dirs + 1;
      children.total.files += item.children.total.files;
    } else {
      item = FileInfos(entry);
      ++children.local.files;
      ++children.total.files;
    }
    size += item.size.bytes;
    items.emplace_back(std::move(item));
  }

  ItemInfos::ItemInfos(fs::directory_entry entry) {
    path = entry.path();
    size = entry.is_directory() ? SizeUnit::SizeUnit() : fs::file_size(path);
    time = Utils::to_time_t(fs::last_write_time(path));
    name = NameInfos(path);
  }

  DirInfos::DirInfos(fs::directory_entry entry, bool hidden) noexcept : ItemInfos(entry) {
    for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it)
      it->is_directory()
        ? push_item<DirInfos>(*it, hidden)
        : push_item<FileInfos>(*it, hidden);
  }
} // namespace FileDirInfos
