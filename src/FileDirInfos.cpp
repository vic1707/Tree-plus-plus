#include <FileDirInfos.hpp>
#include "displayers_specs/Sorter.hpp"
#include "displayers_specs/Filter.hpp"

namespace FileDirInfos {

  void ChildCount::add_file() noexcept {
    ++this->local.files;
    ++this->total.files;
  }

  void ChildCount::remove_file() noexcept {
    --this->local.files;
    --this->total.files;
  }

  void ChildCount::add_dir(const DirInfos& dir) noexcept {
    ++this->local.dirs;
    this->total.dirs += dir.children.total.dirs + 1;
    this->total.files += dir.children.total.files;
  }

  void ChildCount::remove_dir(const DirInfos& dir) noexcept {
    --this->local.dirs;
    this->total.dirs -= dir.children.total.dirs + 1;
    this->total.files -= dir.children.total.files;
  }

  template <Item T>
  inline std::variant<DirInfos, FileInfos> DirInfos::build_item(fs::directory_entry entry, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters, const std::vector<std::unique_ptr<Filter::AFilter>> &filters) {
    T item;
    if constexpr (std::is_same_v<T, DirInfos>) {
      item = DirInfos(entry, sorters, filters);
      this->children.add_dir(item);
    } else {
      item = FileInfos(entry);
      this->children.add_file();
    }
    this->size += item.size;
    return item;
  }

  ItemInfos::ItemInfos(fs::directory_entry entry) :
    path(entry.path()),
    time(Utils::to_time_t(fs::last_write_time(this->path))),
    name(this->path.filename().string()),
    size(entry.is_directory() ? 0 : fs::file_size(this->path))
  {}

  DirInfos::DirInfos(fs::directory_entry entry, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters, const std::vector<std::unique_ptr<Filter::AFilter>> &filters) : ItemInfos(entry) {
    for (fs::directory_iterator it(this->path); it != fs::directory_iterator(); ++it) {
      auto item = it->is_directory()
        ? build_item<DirInfos>(*it, sorters, filters)
        : build_item<FileInfos>(*it, sorters, filters);
      this->items.emplace_back(std::move(item));
    }
    for (const auto &filter : filters)
      filter->filter(*this);
    for (const auto &sorter : sorters)
      sorter->sort(this->items);
  }
} // namespace FileDirInfos
