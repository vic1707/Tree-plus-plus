#pragma once
/* std */
#include <iostream>
#include <string>
/* custom */
#include "file_dir_infos.hpp"

namespace Formatter {
  class AFormatter {
    public:
      /* Members */
      size_t width;
      /* Constructors */
      AFormatter(size_t width) noexcept : width(width) {};
      virtual ~AFormatter() = default;
      /* Methods */
      virtual void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept = 0;
  };
} // namespace Formatter
