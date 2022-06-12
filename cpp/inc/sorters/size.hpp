#pragma once
/* custom */
#include <displayers_specs/sorter.hpp>
#include <SizeUnit.hpp>

namespace Sorter {
  class Size : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
          auto get_size = [](const auto& i) -> SizeUnit {
            if (std::holds_alternative<FileDirInfos::DirInfos>(i))
              return std::get<FileDirInfos::DirInfos>(i).size;
            else
              return std::get<FileDirInfos::FileInfos>(i).size;
          };
          return get_size(a) < get_size(b);
        });
    }
  };
} // namespace Sorter
