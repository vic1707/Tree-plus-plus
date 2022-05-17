#include "file_dir_infos.hpp"

namespace FileDirInfos {
  template <typename ItemT>
  inline void push_item(auto &self, const fs::directory_entry &entry) {
    auto file = typename decltype(self.items)::value_type(std::in_place_type<ItemT>, entry);
    self.size += std::get<ItemT>(file).size.bytes;
    self.items.emplace_back(std::move(file));
  }

  ItemInfos::ItemInfos(const fs::directory_entry &entry) {
    path = entry.path();
    size = fs::file_size(entry.path());
    time = fs::file_time_type::clock::to_time_t(fs::last_write_time(entry.path()));
  }

  DirInfos::DirInfos(const fs::directory_entry &entry) {
    path = entry.path();
    time = fs::file_time_type::clock::to_time_t(fs::last_write_time(entry.path()));
    size = SizeUnit::SizeUnit();
    for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it) {
      if (it->is_directory())
        push_item<DirInfos>(*this, *it);
      else
        push_item<FileInfos>(*this, *it);
    }
  }
} // namespace FileDirInfos
