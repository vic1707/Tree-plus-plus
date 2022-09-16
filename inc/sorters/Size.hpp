#pragma once
/* custom */
#include <displayers_specs/Sorter.hpp>
#include <SizeUnit.hpp>

namespace Sorter {
  class Size : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_sort(items.begin(), items.end(), [this](const auto &a, const auto &b) {
          return get_size(a) < get_size(b);
        });
      }
    private:
      SizeUnit get_size(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).size;
        else
          return std::get<FileDirInfos::FileInfos>(i).size;
      };
  };
} // namespace Sorter
