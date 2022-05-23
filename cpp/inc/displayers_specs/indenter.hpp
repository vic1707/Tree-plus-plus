#ifndef INDENTER_HPP
  #define INDENTER_HPP
  /* std */
  #include <iostream>
  #include <string>
  #include <string_view>
  /* fmt */
  #include <fmt/format.h>
  /* custom */
  #include "file_dir_infos.hpp"
  #include "formatter.hpp"

  namespace fs = std::filesystem;

  class Indenter : virtual public Formatter {
    private:
      /* Members */
      std::string continuity_indent;
      std::string entry_pointer;
      std::string last_entry_pointer;
      std::string last_continuity_indent;

    public:
      /* Constructors */
      Indenter(std::string_view continuity_fill = " ", std::string_view fill_indent = " ", std::string_view entry_ankle = " ", std::string_view last_entry_ankle = " ", size_t tab_size = 2) noexcept :
        continuity_indent(fmt::format("{0: <{1}}", continuity_fill, tab_size)),
        entry_pointer(fmt::format(fmt::runtime(fmt::format(fmt::runtime("{{0:{0}<{{1}}}} "), fill_indent)), entry_ankle, tab_size - 1)),
        last_entry_pointer(fmt::format(fmt::runtime(fmt::format(fmt::runtime("{{0:{0}<{{1}}}} "), fill_indent)), last_entry_ankle, tab_size - 1)),
        last_continuity_indent(std::string(tab_size, ' '))
      {}
      /* Methods */
      void display(const FileDirInfos::DirInfos &item, std::string prefix = "") noexcept;
  };
#endif // INDENTER_HPP
