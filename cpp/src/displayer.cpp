#include "displayer.hpp"

namespace Displayer {
  void Displayer::display(FileDirInfos::DirInfos &directory, std::string prefix) noexcept {
    for (auto &sorter : m_sort)
      sorter->sort(directory.items);

    for (auto &child : directory.items) {
      const auto entry_p = &child == &directory.items.back() ? m_indent->last_entry_pointer : m_indent->entry_pointer;
      const auto continuity_p = &child == &directory.items.back() ? m_indent->last_continuity_indent : m_indent->continuity_indent;
      if (std::holds_alternative<FileDirInfos::DirInfos>(child)) {
        auto &dir = std::get<FileDirInfos::DirInfos>(child);
        m_format->display_folder(&dir, prefix + entry_p);
        display(dir, prefix + continuity_p);
      } else {
        auto &file = std::get<FileDirInfos::FileInfos>(child);
        m_format->display_file(&file, prefix + entry_p);
      }
    }
  }

  Displayer get_indenter(DisplayerOptions options) {
    Displayer displ;

    if (!options.all_files){
      std::cout << "Only directories and files will be displayed.\n";
      displ.add_sorter(std::make_unique<Sorter::NoHiddenFilesOrDirectories>());
    }
    // Sorters
    if (options.sorters.empty())
      displ.add_sorter(std::make_unique<Sorter::Default>());
    else
      for (auto &opt : options.sorters)
        if (opt == "alpha")
          displ.add_sorter(std::make_unique<Sorter::Alpha>());
        else if (opt == "extension")
          displ.add_sorter(std::make_unique<Sorter::Extension>());
        else if (opt == "size")
          displ.add_sorter(std::make_unique<Sorter::Size>());
        else if (opt == "files_folders")
          displ.add_sorter(std::make_unique<Sorter::SeparateFilesFolders<FileDirInfos::FileInfos>>());
        else if (opt == "folders_files")
          displ.add_sorter(std::make_unique<Sorter::SeparateFilesFolders<FileDirInfos::DirInfos>>());

    // Indenter
    if (options.indenter == "space")
      displ.set_indent(std::make_unique<Indenter::Space>(options.tab_size));
    else if (options.indenter == "fancy")
      displ.set_indent(std::make_unique<Indenter::Fancy>(options.tab_size));

    // Formatter
    if (options.formatter == "name_only")
      displ.set_format(std::make_unique<Formatter::NameOnly>(options.columns));
    else if (options.formatter == "full_infos")
      displ.set_format(std::make_unique<Formatter::FullInfos>(options.columns));

    return displ;
  }
} // namespace Displayer
