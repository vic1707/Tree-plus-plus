#include "tree.hpp"

const std::array<std::string_view, 2> Tree::entry_pointers = { "├── ", "└── " };
const std::array<std::string_view, 2> Tree::continuity_pointers = { "│   ", "    " };

void Tree::display_child_file(fs::directory_entry file, std::string prefix) {
  const fs::file_time_type fileTime = fs::last_write_time(file.path());
  const time_t time = decltype(fileTime)::clock::to_time_t(fileTime);

  fs_utils::size_unit readable_size = fs_utils::readable_file_size((double) file.file_size());

  std::cout << prefix
            << file.path().filename().string()
            << " - size: " << readable_size.size << *readable_size.unit
            << " - " << std::asctime(std::localtime(&time));
  files++;
}

void Tree::display_child_dir(fs::directory_entry dir, std::string prefix) {
  fs_utils::size_unit readable_size = fs_utils::readable_dir_size(dir);

  std::cout << prefix
            << dir.path().filename().string()
            << " - size: " << readable_size.size << *readable_size.unit
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
      const std::string_view c_pointer = index == entries.size() - 1
        ? Tree::continuity_pointers[1]
        : Tree::continuity_pointers[0];
      traverse(entries[index], prefix + (std::string) c_pointer);
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
