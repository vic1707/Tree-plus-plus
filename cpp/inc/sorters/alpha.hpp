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
          auto get_path = [](const auto& a) -> std::string {
            if (std::holds_alternative<FileDirInfos::DirInfos>(a))
              return std::get<FileDirInfos::DirInfos>(a).path;
            else
              return std::get<FileDirInfos::FileInfos>(a).path;
          };
          return get_path(a) < get_path(b);
        });
      }
  };
} // namespace Sorter
