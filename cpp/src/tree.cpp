#include "tree.hpp"

const std::array<std::string_view, 2> Tree::entry_pointers = { "├── ", "└── " };
const std::array<std::string_view, 2> Tree::continuity_pointers = { "│   ", "    " };

void Tree::display_child_file(fs::directory_entry file, std::string prefix) {
  const fs::file_time_type fileTime = fs::last_write_time(file.path());
  const time_t time = decltype(fileTime)::clock::to_time_t(fileTime);

  fs_utils::SizeUnit readable_size(file.file_size());

  // fmt::print("{}{} - size: {} - {}\n", prefix, entry_pointers[0], readable_size, fmt::localtime(&time));

  std::cout << prefix
            << file.path().filename().string()
            << " - size: " << readable_size
            << " - " << std::asctime(std::localtime(&time));
  files++;
}

void Tree::display_child_dir(fs::directory_entry dir, std::string prefix) {
  fs_utils::SizeUnit readable_size = fs_utils::readable_dir_size(dir);

  std::cout << prefix
            << dir.path().filename().string()
            << " - size: " << readable_size
            << "\n";
  dirs++;
}

void Tree::traverse(fs::directory_entry dir, std::string prefix = "") {
  std::vector<fs::directory_entry> entries;
  if (options.dirs_first)
    entries = fs_utils::list_dirs_first(dir, options.all_files);
  else if (options.files_first)
    entries = fs_utils::list_files_first(dir, options.all_files);
  else
    entries = fs_utils::list_entries_of_dir(dir, options.all_files);


  for (size_t index = 0; index < entries.size(); index++) {
    const std::string_view entry_pointer = index == entries.size() - 1
      ? Tree::entry_pointers[1]
      : Tree::entry_pointers[0];

    if (!entries[index].is_directory())
      display_child_file(entries[index], prefix + (std::string) entry_pointer);
    else {
      display_child_dir(entries[index], prefix + (std::string) entry_pointer);
      traverse(entries[index], prefix + (std::string) continuity_pointer);
    }
  }
}

Tree::Tree(std::string_view p, arguments::options opt): options(opt), path(fs::canonical(p).filename().string()) {
  continuity_pointer = options.foldable
    ? Tree::continuity_pointers[1]
    : Tree::continuity_pointers[0];

  fs::directory_entry dir = fs::directory_entry(p);
  size = fs_utils::readable_dir_size(dir);

  if (options.redirect) freopen((path+".tree").c_str(),"w",stdout); // redirect stdout to file <path>.tree

  std::cout << path << "\n";
  traverse(dir);
  summary();
}

ItemInfo::ItemInfo(const fs::directory_entry& entry) {
  path = entry.path();
  size = fs::file_size(entry.path());
  time = fs::file_time_type::clock::to_time_t(fs::last_write_time(entry.path()));
}
FileInfo::FileInfo(const fs::directory_entry& entry) : ItemInfo(entry) {
  
}
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
Tree2::Tree2(std::string_view path) : root(fs::directory_entry(path)) {
  
}

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