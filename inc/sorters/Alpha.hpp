#pragma once
/* std */
#include <string>
/* custom */
#include <displayers_specs/Sorter.hpp>

namespace Sorter {
  class Alpha : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_sort(items.begin(), items.end(), [this](const auto &a, const auto &b) {
          return this->get_path(a) < this->get_path(b);
        });
      }
    private:
      fs::path get_path(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).path;
        else
          return std::get<FileDirInfos::FileInfos>(i).path;
      };
  };
} // namespace Sorter
