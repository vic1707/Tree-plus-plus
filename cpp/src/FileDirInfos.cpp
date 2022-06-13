#include <FileDirInfos.hpp>

namespace FileDirInfos {
  template <typename Item>
  inline std::variant<DirInfos, FileInfos> DirInfos::build_item(fs::directory_entry entry, bool hidden) {
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
    return item;
  }

  ItemInfos::ItemInfos(fs::directory_entry entry) {
    path = entry.path();
    size = entry.is_directory() ? SizeUnit() : fs::file_size(path);
    time = Utils::to_time_t(fs::last_write_time(path));
    name = NameInfos(path);
  }

  DirInfos::DirInfos(fs::directory_entry entry, bool hidden) : ItemInfos(entry) {
    for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it) {
      if (!hidden && entry.path().filename().string().front() == '.') continue;
      auto item = it->is_directory()
        ? build_item<DirInfos>(*it, hidden)
        : build_item<FileInfos>(*it, hidden);
      items.emplace_back(std::move(item));
    }
  }
} // namespace FileDirInfos
