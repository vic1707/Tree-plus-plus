#include "tree.hpp"

const std::array<std::string_view, 2> Tree::entry_pointers = { "├── ", "└── " };
const std::array<std::string_view, 2> Tree::continuity_pointers = { "│   ", "    " };

inline void Tree::summary() {
  std::cout << "\n" << dirs << " directories, " << files << " files - size: " << size.size << *size.unit << ".\n";
}

void Tree::display_child_file(fs::directory_entry file, std::string prefix) {
  const fs::file_time_type fileTime = fs::last_write_time(file.path());
  const time_t time = decltype(fileTime)::clock::to_time_t(fileTime);

  utils::size_unit readable_size = utils::readable_file_size((float) file.file_size());

  std::cout << prefix
            << file.path().filename().string()
            << " - size: " << readable_size.size << *readable_size.unit
            << " - " << std::asctime(std::localtime(&time));
  files++;
}

inline void Tree::display_child_dir(fs::directory_entry dir, std::string prefix) {
  utils::size_unit readable_size = utils::readable_dir_size(dir);

  std::cout << prefix
            << dir.path().filename().string()
            << " - size: " << readable_size.size << *readable_size.unit
            << "\n";
  dirs++;
}

void Tree::traverse(fs::directory_entry dir, std::string prefix = "") {
  std::vector<fs::directory_entry> entries;
  for (const fs::directory_entry &entry : fs::directory_iterator(dir))
    if (options.all_files || !entry.path().filename().string().starts_with("."))
      entries.push_back(entry);

  sort(entries.begin(), entries.end(), [](const fs::directory_entry &left, const fs::directory_entry &right) -> bool {
    return left.path().filename() < right.path().filename();
  });

  for (size_t index = 0; index < entries.size(); index++) {
    const std::string_view* entry_pointer = index == entries.size() - 1
      ? &(Tree::entry_pointers[1])
      : &(Tree::entry_pointers[0]);

    if (!entries[index].is_directory())
      display_child_file(entries[index], prefix + (std::string) *entry_pointer);
    else {
      display_child_dir(entries[index], prefix + (std::string) *entry_pointer);
      traverse(entries[index], prefix + (std::string) *continuity_pointer);
    }
  }
  dirs++;
}

Tree::Tree(char* p, arguments::options opt): options(opt), path(fs::canonical(p).filename().string()) {
  continuity_pointer = options.foldable
    ? &(Tree::continuity_pointers[1])
    : &(Tree::continuity_pointers[0]);

  fs::directory_entry dir = fs::directory_entry(p);
  size = utils::readable_dir_size(dir);

  if (options.redirect) freopen((path+".tree").c_str(),"w",stdout); // redirect stdout to file <path>.tree

  std::cout << path << "\n";
  traverse(dir);
}

Tree::~Tree() {
  summary();
}
