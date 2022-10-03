#pragma once
/* custom */
#include <displayers_specs/Filter.hpp>
#include <iostream>

namespace Filter {
  class Hidden : public AFilter {
    public:
      void filter(FileDirInfos::DirInfos &parent) final {
        for (auto it = parent.items.begin(); it != parent.items.end(); ++it) {
          if (this->get_filename(*it).front() != '.') continue;
          remove_from_parent(it, parent);
          --it;
        }
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
