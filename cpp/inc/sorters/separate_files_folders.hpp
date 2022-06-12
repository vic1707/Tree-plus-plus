#pragma once
/* custom */
#include "displayers_specs/sorter.hpp"

namespace Sorter {
  template <typename T>
  concept FileDir = std::same_as<T, FileDirInfos::FileInfos> || std::same_as<T, FileDirInfos::DirInfos>;

  template <FileDir First>
  class SeparateFilesFolders : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_partition(items.begin(), items.end(), [](const auto &item) {
          return std::holds_alternative<First>(item);
        });
      };
  };
} // namespace Sorter
