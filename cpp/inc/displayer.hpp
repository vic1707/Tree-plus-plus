#pragma once
/* std */
#include <string>
#include <string_view>
#include <vector>
/* custom */
// specs
#include "displayers_specs/indenter.hpp"
#include "displayers_specs/formatter.hpp"
#include "displayers_specs/sorter.hpp"
// formatters
#include "formatters/name_only.hpp"
#include "formatters/full_infos.hpp"
// indenters
#include "indenters/fancy.hpp"
#include "indenters/space.hpp"
// sorters
#include "sorters/alpha.hpp"
#include "sorters/default.hpp"
#include "sorters/size.hpp"
#include "sorters/extension.hpp"
#include "sorters/separate_files_folders.hpp"

namespace Displayer {
  class Displayer {
    private:
      std::unique_ptr<Indenter::IndenterOptions> m_indent;
      std::unique_ptr<Formatter::AFormatter> m_format;
      std::vector<std::unique_ptr<Sorter::ASorter>> m_sort;

    public:
      void display(FileDirInfos::DirInfos &item, std::string prefix = "") noexcept;
      void set_indent(std::unique_ptr<Indenter::IndenterOptions> indent) { m_indent = std::move(indent); }
      void set_format(std::unique_ptr<Formatter::AFormatter> format) { m_format = std::move(format); }
      void add_sort(std::unique_ptr<Sorter::ASorter> sort) { m_sort.push_back(std::move(sort)); }
  };

  // std::unique_ptr<Displayer> get_indenter(std::string_view opt);
  Displayer get_indenter(std::string_view opt, size_t size_tab = 2);
}
