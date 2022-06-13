#include <FileDirInfos.hpp>

namespace FileDirInfos {
  template <typename Item>
  inline std::variant<DirInfos, FileInfos> DirInfos::build_item(fs::directory_entry entry, bool hidden) {
    Item item;
    if constexpr (std::is_same_v<Item, DirInfos>) {
      item = DirInfos(entry, hidden);
      ++this->children.local.dirs;
      this->children.total.dirs += item.children.total.dirs + 1;
      this->children.total.files += item.children.total.files;
    } else {
      item = FileInfos(entry);
      ++this->children.local.files;
      ++this->children.total.files;
    }
    this->size += item.size.bytes;
    return item;
  }

  ItemInfos::ItemInfos(fs::directory_entry entry) :
    path(entry.path()),
    time(Utils::to_time_t(fs::last_write_time(this->path))),
    name(NameInfos(this->path)),
    size(entry.is_directory() ? SizeUnit() : fs::file_size(this->path))
  {}

  DirInfos::DirInfos(fs::directory_entry entry, bool hidden) : ItemInfos(entry) {
    for (fs::directory_iterator it(this->path); it != fs::directory_iterator(); ++it) {
      if (!hidden && entry.path().filename().string().front() == '.') continue;
      auto item = it->is_directory()
        ? build_item<DirInfos>(*it, hidden)
        : build_item<FileInfos>(*it, hidden);
      this->items.emplace_back(std::move(item));
    }
  }
} // namespace FileDirInfos
