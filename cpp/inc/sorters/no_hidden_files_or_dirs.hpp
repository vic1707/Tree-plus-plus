#pragma once
/* std */
#include <string>
/* custom */
#include "displayers_specs/sorter.hpp"

namespace Sorter {
  class NoHiddenFilesOrDirectories : public ASorter {
    public:
      void sort(Items &items) noexcept {
        // remove all hidden files or directories
        std::erase_if(items, [](const auto &item) {
          if (std::holds_alternative<FileDirInfos::FileInfos>(item))
            return std::get<FileDirInfos::FileInfos>(item).name.filename.front() == '.';
          else
            return std::get<FileDirInfos::DirInfos>(item).name.filename.front() == '.';
        });
      }
  };
} // namespace Sorter
