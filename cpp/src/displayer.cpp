#include "displayer.hpp"

namespace Displayer {
  void Displayer::display(FileDirInfos::DirInfos &directory, std::string prefix) noexcept {
    m_sort->sort(directory.items);
    m_separator->separate(directory.items);
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

  Displayer get_indenter(std::string_view opt, size_t size_tab) {
    Displayer disp;
    if (opt == "classic") {
      disp.set_format(std::make_unique<Formatter::NameOnly>());
      disp.set_indent(std::make_unique<Indenter::Space>(size_tab));
      disp.set_sort(std::make_unique<Sorter::Default>());
      disp.set_separator(std::make_unique<Separator::Default>());
    } else if (opt == "fancy") {
      disp.set_format(std::make_unique<Formatter::FullInfos>());
      disp.set_indent(std::make_unique<Indenter::Fancy>(size_tab));
      disp.set_sort(std::make_unique<Sorter::Alpha>());
      disp.set_separator(std::make_unique<Separator::FileFolder<FileDirInfos::FileInfos, FileDirInfos::DirInfos>>());
    } else {
      throw std::runtime_error("Unknown indenter");
    }
    return disp;
  }
} // namespace Displayer
