#pragma once
/* std */
#include <set>
#include <string>
#include <string_view>
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
#include "sorters/separate_files_folders.hpp"
#include "sorters/size.hpp"

namespace Displayer {
  struct DisplayerOptions {
    std::set<std::string_view> sorters;
    std::string_view formatter;
    std::string_view indenter;
    size_t columns;
    size_t tab_size;
    bool redirect;
  };

  class Displayer {
    private:
      std::unique_ptr<Indenter::IndenterOptions> m_indent;
      std::unique_ptr<Formatter::AFormatter> m_format;
      std::vector<std::unique_ptr<Sorter::ASorter>> m_sort;
      void display(FileDirInfos::DirInfos &item, std::string prefix = "") noexcept;


    public:
      void traverse(FileDirInfos::DirInfos &item, bool &redirect) noexcept;
      void set_indent(std::unique_ptr<Indenter::IndenterOptions> indent) { m_indent = std::move(indent); }
      void set_format(std::unique_ptr<Formatter::AFormatter> format) { m_format = std::move(format); }
      void add_sorter(std::unique_ptr<Sorter::ASorter> sort) { m_sort.push_back(std::move(sort)); }
  };

  Displayer &get_indenter(DisplayerOptions options);
}
