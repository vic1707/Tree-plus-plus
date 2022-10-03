#pragma once
/* std */
#include <iostream>
#include <string>
/* fmt */
#include <fmt/format.h>
#include <fmt/ostream.h>
/* custom */
#include <displayers_specs/Formatter.hpp>
#include <FileDirInfos.hpp>
#include <Utils.hpp>

namespace Formatter {
  class FullInfos : public AFormatter {
    public:
      /* Methods */
      void display_file(const FileDirInfos::FileInfos *item, std::string_view prefix) final {
        char buff[20];
        std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
        auto left_side = fmt::format("{0}{1}", prefix, item->name);
        auto right_side = fmt::format("{0} - {1}", item->size, buff);
        fmt::format_to(this->stream, "{0}{1: >{2}}\n", left_side, right_side, this->width - Utils::utf8_len(left_side));
      }

      void display_folder(const FileDirInfos::DirInfos *item, std::string_view prefix) final {
        char buff[20];
        std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
        auto left_side = fmt::format("{0}{1} - {2}", prefix, item->name, item->children);
        auto right_side = fmt::format("{0} - {1}", item->size, buff);
        fmt::format_to(this->stream, "{0}{1: >{2}}\n", left_side, right_side, this->width - Utils::utf8_len(left_side));
      }
      /* Constructor */
      FullInfos(size_t w) noexcept : AFormatter(w) {};
  };
} // namespace Formatter
