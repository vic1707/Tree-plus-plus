#pragma once
/* std */
#include <string>
/* custom */
#include <displayers_specs/sorter.hpp>

namespace Sorter {
  class Extension : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
          auto get_extension = [](const auto &i) -> std::string {
            if (std::holds_alternative<FileDirInfos::DirInfos>(i))
              return std::get<FileDirInfos::DirInfos>(i).name.extension;
            else
              return std::get<FileDirInfos::FileInfos>(i).name.extension;
          };
          return get_extension(a) < get_extension(b);
        });
      }
  };
} // namespace Sorter
