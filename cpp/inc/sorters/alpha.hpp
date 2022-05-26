#pragma once
/* std */
#include <string>
/* custom */
#include "displayers_specs/sorter.hpp"

namespace Sorter {
  class Alpha : public ASorter {
    public:
      void sort(Items &items) noexcept {
        std::stable_sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
          auto get_path = [](const auto& i) -> std::string {
            if (std::holds_alternative<FileDirInfos::DirInfos>(i))
              return std::get<FileDirInfos::DirInfos>(i).path;
            else
              return std::get<FileDirInfos::FileInfos>(i).path;
          };
          return get_path(a) < get_path(b);
        });
      }
  };
} // namespace Sorter
