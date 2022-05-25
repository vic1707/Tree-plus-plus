#include "file_dir_infos.hpp"

namespace FileDirInfos {
  template <typename Item>
  inline constexpr void push_item(auto &self, const fs::directory_entry &entry) noexcept {
    auto file = typename decltype(self.items)::value_type(std::in_place_type<Item>, entry);
    self.size += std::get<Item>(file).size.bytes;
    self.items.emplace_back(std::move(file));
  }

  ItemInfos::ItemInfos(const fs::directory_entry &entry) noexcept {
    path = entry.path();
    size = fs::file_size(path);
    time = Utils::to_time_t(fs::last_write_time(path));
  }

  DirInfos::DirInfos(const fs::directory_entry &entry) noexcept {
    path = entry.path();
    time = Utils::to_time_t(fs::last_write_time(path));
    size = SizeUnit::SizeUnit();
    for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it)
      it->is_directory()
        ? push_item<DirInfos>(*this, *it)
        : push_item<FileInfos>(*this, *it);
  }
} // namespace FileDirInfos
