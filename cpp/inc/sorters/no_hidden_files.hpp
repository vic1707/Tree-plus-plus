#pragma once
/* std */
#include <string>
/* custom */
#include "displayers_specs/sorter.hpp"

namespace Sorter {
  class NoHiddenFiles : public ASorter {
    public:
      void sort(Items &items) noexcept {
        // remove all hidden files
        items.erase(std::remove_if(items.begin(), items.end(), [](const auto &item) {
          if (std::holds_alternative<FileDirInfos::FileInfos>(item)) {
            auto &file = std::get<FileDirInfos::FileInfos>(item);
            return file.name.filename.front() == '.';
          }
          return false;
        }), items.end());
      }
  };
} // namespace Sorter
