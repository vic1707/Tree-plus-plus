#pragma once
/* std */
#include <iostream>
#include <string>
/* custom */
#include "displayers_specs/formatter.hpp"
#include "file_dir_infos.hpp"

namespace Formatter {
  class FullInfos : public AFormatter {
    public:
      /* Methods */
      void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept override {
        char buff[20];
        std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
        std::cout << prefix << item->name.filename << " - " << item->size << " - " << buff << "\n";
      }

      void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept override {
        char buff[20];
        std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
        std::cout << prefix << item->name.filename << " - " << item->size << " - " << buff << "\n";
      }
      /* Constructor */
      FullInfos(size_t width) noexcept : AFormatter(width) {};
  };
} // namespace Formatter
