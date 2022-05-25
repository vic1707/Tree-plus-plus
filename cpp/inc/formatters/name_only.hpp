#pragma once
/* std */
#include <iostream>
#include <string>
/* custom */
#include "displayers_specs/formatter.hpp"
#include "file_dir_infos.hpp"

namespace Formatter {
  class NameOnly : public AFormatter {
    public:
      void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept override {
        std::cout << prefix << item->name.filename << "\n";
      }

      void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept override {
        std::cout << prefix << item->name.filename << "\n";
      }
  };
} // namespace Formatter
