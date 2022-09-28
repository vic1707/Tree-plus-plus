#pragma once
/* custom */
#include <displayers_specs/Filter.hpp>

namespace Filter {
  class Hidden : public AFilter {
    public:
      void filter(Items &items) final {
        for (auto it = items.begin(); it != items.end(); ++it) {
          if (this->get_filename(*it).front() != '.') return;
          items.erase(it);
          --it;
        }
      }
    private:
      std::string get_filename(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).name.filename;
        else
          return std::get<FileDirInfos::FileInfos>(i).name.filename;
      };
  };
} // namespace Sorter
