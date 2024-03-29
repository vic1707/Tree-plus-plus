#pragma once
/* std */
#include <iostream>
#include <string>
/* custom */
#include <displayers_specs/Formatter.hpp>
#include <FileDirInfos.hpp>

namespace Formatter {
  class NameOnly : public AFormatter {
    public:
      /* Methods */
      void display_file(const FileDirInfos::FileInfos *item, std::string_view prefix) final {
        fmt::format_to(this->stream, "{}{}\n", prefix, item->name);
      }

      void display_folder(const FileDirInfos::DirInfos *item, std::string_view prefix) final {
        fmt::format_to(this->stream, "{}{}\n", prefix, item->name);
      }
      /* Constructor */
      NameOnly(size_t w) noexcept : AFormatter(w) {};
  };
} // namespace Formatter
