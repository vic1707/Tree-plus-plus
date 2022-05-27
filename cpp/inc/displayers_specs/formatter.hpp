#pragma once
/* std */
#include <string>
/* custom */
#include "file_dir_infos.hpp"

namespace Formatter {
  class AFormatter {
    protected:
      /* Members */
      size_t width;
    public:
      /* Constructors */
      AFormatter(size_t w) noexcept : width(w) {};
      virtual ~AFormatter() = default;
      /* Methods */
      virtual void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept = 0;
  };
} // namespace Formatter
