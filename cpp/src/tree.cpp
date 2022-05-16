#include "tree.hpp"

// const std::array<std::string_view, 2> entry_pointers = { "├── ", "└── " };
// const std::array<std::string_view, 2> continuity_pointers = { "│   ", "    " };

ItemInfo::ItemInfo(const fs::directory_entry& entry) {
  path = entry.path();
  size = fs::file_size(entry.path());
  time = fs::file_time_type::clock::to_time_t(fs::last_write_time(entry.path()));
}
FileInfo::FileInfo(const fs::directory_entry& entry) : ItemInfo(entry) {}

template<typename ItemT>
inline auto make_item(auto& self, const fs::directory_entry& entry) {
  auto file = typename decltype(self.items)::value_type(std::in_place_type<ItemT>, entry);
  self.size += std::get<ItemT>(file).size.bytes;
  return file;
}
DirInfo::DirInfo(const fs::directory_entry& entry) {
  path = entry.path();
  time = fs::file_time_type::clock::to_time_t(fs::last_write_time(entry.path()));
  size = fs_utils::SizeUnit();
  for (fs::directory_iterator it(path); it != fs::directory_iterator(); ++it) {
    if (it->is_directory())
      items.emplace_back(make_item<DirInfo>(*this, *it));
    else
      items.emplace_back(make_item<FileInfo>(*this, *it));
  }

}

Tree::Tree(std::string_view path) : root(fs::directory_entry(path)) {}

void Classic::display(const Item& item, size_t tab) {
  for (size_t i = 0; i < tab; i++)
    std::cout.write("  ", 2);
  if (std::holds_alternative<DirInfo>(item)) {
    auto& dir = std::get<DirInfo>(item);
    display_info(&dir);
    for(auto& file : dir.items)
      display(file, tab + 1);
  } else {
    auto& file = std::get<FileInfo>(item);
    display_info(&file);
  }
}

void Classic::display_info(const ItemInfo* info) {
  char buf[64];
  auto tmval = std::localtime(&info->time);
  strftime(buf, sizeof buf, "%A %c", tmval);
  std::cout << info->path.filename().string() << " - " << info->size << " - " << buf << '\n';
}

// pour le tri la fct partition