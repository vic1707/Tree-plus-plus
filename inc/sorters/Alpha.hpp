#pragma once
/* std */
#include <algorithm>
#include <string>
/* custom */
#include <displayers_specs/Sorter.hpp>

namespace Sorter {
  class Alpha : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_sort(items.begin(), items.end(), [this](const auto &a, const auto &b) {
          std::string a_path = this->get_filename(a);
          std::string b_path = this->get_filename(b);
          Utils::word_to_lower(a_path);
          Utils::word_to_lower(b_path);
          return a_path < b_path;
        });
      }
    private:
      std::string get_filename(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).name;
        else
          return std::get<FileDirInfos::FileInfos>(i).name;
      };
  };
} // namespace Sorter
