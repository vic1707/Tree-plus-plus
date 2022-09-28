#include <FileDirInfos.hpp>
#include "displayers_specs/Sorter.hpp"
#include "displayers_specs/Filter.hpp"

namespace FileDirInfos {

  constexpr void ChildCount::add_file() noexcept {
    ++this->local.files;
    ++this->total.files;
  }

  constexpr void ChildCount::add_dir(const DirInfos& dir) noexcept {
      ++this->local.dirs;
      this->total.dirs += dir.children.total.dirs + 1;
      this->total.files += dir.children.total.files;
    }

  template <typename Item>
  inline std::variant<DirInfos, FileInfos> DirInfos::build_item(fs::directory_entry entry, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters, const std::vector<std::unique_ptr<Filter::AFilter>> &filters) {
    Item item;
    if constexpr (std::is_same_v<Item, DirInfos>) {
      item = DirInfos(entry, sorters, filters);
      this->children.add_dir(item);
    } else {
      item = FileInfos(entry);
      this->children.add_file();
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

  DirInfos::DirInfos(fs::directory_entry entry, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters, const std::vector<std::unique_ptr<Filter::AFilter>> &filters) : ItemInfos(entry) {
    for (fs::directory_iterator it(this->path); it != fs::directory_iterator(); ++it) {
      auto item = it->is_directory()
        ? build_item<DirInfos>(*it, sorters, filters)
        : build_item<FileInfos>(*it, sorters, filters);
      this->items.emplace_back(std::move(item));
    }
    for (const auto &sorter : sorters)
      sorter->sort(this->items);
    for (const auto &filter : filters)
      filter->filter(this->items);
  }
} // namespace FileDirInfos
