#pragma once
/* std */
#include <iostream>
#include <string>
/* fmt */
#include <fmt/format.h>
#include <fmt/ostream.h>
/* custom */
#include "displayers_specs/formatter.hpp"
#include "file_dir_infos.hpp"
#include "utils.hpp"

namespace Formatter {
  class FullInfos : public AFormatter {
    public:
      /* Methods */
      void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept override {
        char buff[20];
        std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
        auto prefix_name = fmt::format("{0}{1}", prefix, item->name.filename);
        auto size_date = fmt::format("{0} - {1}", item->size, buff);
        std::cout << fmt::format("{0}{1: >{2}}\n", prefix_name, size_date, width - Utils::utf8_len(prefix_name));
      }

      void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept override {
        char buff[20];
        std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
        auto prefix_name = fmt::format("{0}{1}", prefix, item->name.filename);
        auto size_date = fmt::format("{0} - {1}", item->size, buff);
        std::cout << fmt::format("{0}{1: >{2}}\n", prefix_name, size_date, width - Utils::utf8_len(prefix_name));
      }
      /* Constructor */
      FullInfos(size_t width) noexcept : AFormatter(width) {};
  };
} // namespace Formatter
