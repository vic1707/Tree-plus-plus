/* std */
#include <fstream>
/* custom */
#include <Displayer.hpp>
#include <Exception.hpp>
// formatters
#include <formatters/full_infos.hpp>
#include <formatters/name_only.hpp>
// indenters
#include <indenters/fancy.hpp>
#include <indenters/space.hpp>

namespace Displayer {
  Displayer::Displayer(const model::Options &options): m_options(options) {
    // create indenter
    if (m_options.indenter == "space")
      m_indent = std::make_unique<Indenter::Space>(m_options.tab_size);
    else if (m_options.indenter == "fancy" || m_options.indenter.empty())
      m_indent = std::make_unique<Indenter::Fancy>(m_options.tab_size);
    else
      throw Exception(fmt::format("Unknown indenter: '{}'", m_options.indenter));

    // Formatter
    if (m_options.formatter == "name_only" || m_options.formatter.empty() )
      m_format = (std::make_unique<Formatter::NameOnly>(m_options.columns));
    else if (m_options.formatter == "full_infos")
      m_format = (std::make_unique<Formatter::FullInfos>(m_options.columns));
    else
      throw Exception(fmt::format("Unknown formatter: '{}'", m_options.formatter));

    m_stream = &std::cout;
  }

  void Displayer::display(const std::vector<FileDirInfos::DirInfos> &dirs) {
    std::ofstream file;
    for (const auto &directory : dirs) {
      if (m_options.redirect) {
        file = std::ofstream(directory.name.filename + ".tree");
        m_stream = &file;
      }
      m_format->set_stream(m_stream);
      getStream() << directory.name.filename << "\n";
      display_dir(directory);
      getStream() << "\n" << directory.children << " - " << directory.size << "\n";
    }
  }

  void Displayer::display_dir(const FileDirInfos::DirInfos &directory, std::string prefix) {
    auto prefixes = std::array{
      prefix + m_indent->entry_pointer,
      prefix + m_indent->continuity_indent,
      prefix + m_indent->last_entry_pointer,
      prefix + m_indent->last_continuity_indent,
    };

    for (auto &child : directory.items) {
      size_t is_last = int(&child == &directory.items.back()) << 1;
      if (std::holds_alternative<FileDirInfos::DirInfos>(child)) {
        auto &dir = std::get<FileDirInfos::DirInfos>(child);
        m_format->display_folder(&dir, prefixes[is_last + 0]);
        display_dir(dir, prefixes[is_last + 1]);
      } else {
        auto &file = std::get<FileDirInfos::FileInfos>(child);
        m_format->display_file(&file, prefixes[is_last + 0]);
      }
    }
  }
} // namespace Displayer
