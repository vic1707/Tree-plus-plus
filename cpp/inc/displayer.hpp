#ifndef DISPLAYERS_HPP
  #define DISPLAYERS_HPP
  /* std */
  #include <string>
  #include <string_view>
  /* custom */
  // specs
  #include "displayers_specs/indenter.hpp"
  #include "displayers_specs/formatter.hpp"
  // formatters
  #include "formatters/name_only.hpp"
  #include "formatters/full_infos.hpp"
  // indenters
  #include "indenters/fancy.hpp"
  #include "indenters/space.hpp"

  namespace Displayer {
    class Displayer {
      private:
        std::unique_ptr<Indenter::AIndenter> m_indent;
        std::unique_ptr<Formatter::AFormatter> m_format;
      public:
        void display(const FileDirInfos::DirInfos &item, std::string prefix = "") noexcept;
        void set_indent(std::unique_ptr<Indenter::AIndenter> indent) { m_indent = std::move(indent); }
        void set_format(std::unique_ptr<Formatter::AFormatter> format) { m_format = std::move(format); }
    };

    // std::unique_ptr<Displayer> get_indenter(std::string_view opt);
    Displayer get_indenter(std::string_view opt, size_t size_tab = 2);
  }
#endif // DISPLAYERS_HPP
