#pragma once
/* std */
#include <string>
#include <string_view>
#include <vector>
/* custom */
// specs
#include "displayers_specs/formatter.hpp"
#include "displayers_specs/indenter.hpp"
#include "displayers_specs/sorter.hpp"
// formatters
#include "formatters/full_infos.hpp"
#include "formatters/name_only.hpp"
// indenters
#include "indenters/fancy.hpp"
#include "indenters/space.hpp"
// sorters
#include "sorters/alpha.hpp"
#include "sorters/default.hpp"
#include "sorters/extension.hpp"
#include "sorters/no_hidden_files.hpp"
#include "sorters/separate_files_folders.hpp"
#include "sorters/size.hpp"

namespace Displayer {
  struct DisplayerOptions {
    std::vector<std::string_view> sorters;
    std::string_view formatter;
    std::string_view indenter;
    size_t columns;
  };

  class Displayer {
    private:
      std::unique_ptr<Indenter::IndenterOptions> m_indent;
      std::unique_ptr<Formatter::AFormatter> m_format;
      std::vector<std::unique_ptr<Sorter::ASorter>> m_sort;

    public:
      void display(FileDirInfos::DirInfos &item, std::string prefix = "") noexcept;
      void set_indent(std::unique_ptr<Indenter::IndenterOptions> indent) { m_indent = std::move(indent); }
      void set_format(std::unique_ptr<Formatter::AFormatter> format) { m_format = std::move(format); }
      void add_sorter(std::unique_ptr<Sorter::ASorter> sort) { m_sort.push_back(std::move(sort)); }
  };

  Displayer get_indenter(DisplayerOptions options, size_t size_tab = 2);
}
