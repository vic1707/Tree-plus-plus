/* std */
#include <fstream>
/* custom */
#include <Displayer.hpp>
#include <Exception.hpp>
// formatters
#include <formatters/Full_infos.hpp>
#include <formatters/Name_only.hpp>
// indenters
#include <indenters/Fancy.hpp>
#include <indenters/Space.hpp>

namespace Displayer {
  Displayer::Displayer(const model::Options &options): m_options(options) {
    // create indenter
    if (this->m_options.indenter == "space")
      this->m_indent = std::make_unique<Indenter::Space>(this->m_options.tab_size);
    else if (this->m_options.indenter == "fancy" || this->m_options.indenter.empty())
      this->m_indent = std::make_unique<Indenter::Fancy>(this->m_options.tab_size);
    else
      throw Exception(fmt::format("Unknown indenter: '{}'", this->m_options.indenter));

    // Formatter
    if (this->m_options.formatter == "name_only" || this->m_options.formatter.empty() )
      this->m_format = (std::make_unique<Formatter::NameOnly>(this->m_options.columns));
    else if (this->m_options.formatter == "full_infos")
      this->m_format = (std::make_unique<Formatter::FullInfos>(this->m_options.columns));
    else
      throw Exception(fmt::format("Unknown formatter: '{}'", this->m_options.formatter));

    this->m_stream = &std::cout;
  }

  void Displayer::display(const std::vector<FileDirInfos::DirInfos> &dirs) {
    std::ofstream file;
    for (const auto &directory : dirs) {
      if (this->m_options.redirect) {
        file = std::ofstream(directory.name + ".tree");
        this->m_stream = &file;
      }
      this->m_format->set_stream(this->m_stream);
      *this->m_stream << directory.name << "\n";
      display_dir(directory);
      *this->m_stream << "\n" << directory.children << " - " << directory.size << "\n\n";
    }
  }

  void Displayer::display_dir(const FileDirInfos::DirInfos &directory, std::string prefix) {
    auto prefixes = std::array{
      prefix + this->m_indent->entry_pointer,
      prefix + this->m_indent->continuity_indent,
      prefix + this->m_indent->last_entry_pointer,
      prefix + this->m_indent->last_continuity_indent,
    };

    for (auto &child : directory.items) {
      size_t is_last = int(&child == &directory.items.back()) << 1;
      if (std::holds_alternative<FileDirInfos::DirInfos>(child)) {
        auto &dir = std::get<FileDirInfos::DirInfos>(child);
        this->m_format->display_folder(&dir, prefixes[is_last + 0]);
        display_dir(dir, prefixes[is_last + 1]);
        continue;
      }
      auto &file = std::get<FileDirInfos::FileInfos>(child);
      this->m_format->display_file(&file, prefixes[is_last + 0]);
    }
  }
} // namespace Displayer
