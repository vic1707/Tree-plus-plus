#pragma once
/* std */
#include <string>
/* custom */
#include <displayers_specs/Sorter.hpp>

namespace Sorter {
  class Extension : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_sort(items.begin(), items.end(), [this](const auto &a, const auto &b) {
          return this->get_extension(a) < this->get_extension(b);
        });
      }
    private:
      std::string get_extension(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).name.extension;
        else
          return std::get<FileDirInfos::FileInfos>(i).name.extension;
      };
  };
} // namespace Sorter
