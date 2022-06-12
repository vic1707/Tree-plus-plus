#pragma once
/* std */
#include <string>
#include <string_view>
/* fmt */
#include <fmt/format.h>
/* custom */
#include "file_dir_infos.hpp"

namespace fs = std::filesystem;

namespace Indenter {
  struct IndenterOptions {
    /* Members */
    std::string continuity_indent;
    std::string entry_pointer;
    std::string last_entry_pointer;
    std::string last_continuity_indent;
    /* Constructors */
    IndenterOptions(std::string_view continuity_fill = " ", std::string_view fill_indent = " ", std::string_view entry_ankle = " ", std::string_view last_entry_ankle = " ", size_t tab_size = 2) noexcept :
      continuity_indent(fmt::format("{0: <{1}}", continuity_fill, tab_size)),
      entry_pointer(fmt::format(fmt::runtime(fmt::format("{{0:{0}<{{1}}}} ", fill_indent)), entry_ankle, tab_size - 1)),
      last_entry_pointer(fmt::format(fmt::runtime(fmt::format("{{0:{0}<{{1}}}} ", fill_indent)), last_entry_ankle, tab_size - 1)),
      last_continuity_indent(std::string(tab_size, ' '))
    {}
  };
} // namespace Indenter
