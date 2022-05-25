#pragma once
/* custom */
#include "displayers_specs/sorter.hpp"

namespace Sorter {
  class Size : public ASorter {
    public:
      void sort(Items &items) final override {
        std::stable_sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
          auto get_size = [](const auto& a) -> SizeUnit::SizeUnit {
            if (std::holds_alternative<FileDirInfos::DirInfos>(a))
              return std::get<FileDirInfos::DirInfos>(a).size;
            else
              return std::get<FileDirInfos::FileInfos>(a).size;
          };
          return get_size(a) < get_size(b);
        });
    }
  };
} // namespace Sorter
