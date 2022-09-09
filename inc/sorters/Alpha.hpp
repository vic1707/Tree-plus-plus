#pragma once
/* std */
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
/* custom */
#include <displayers_specs/Sorter.hpp>

inline void char_to_lower(char& c) { c = std::tolower(c); };
inline void word_to_lower(std::string& w) {
  std::for_each(w.begin(), w.end(), char_to_lower);
}

namespace Sorter {
  class Alpha : public ASorter {
    public:
      void sort(Items &items) final {
        std::stable_sort(items.begin(), items.end(), [this](const auto &a, const auto &b) {
          std::string a_path = this->get_filename(a);
          std::string b_path = this->get_filename(b);
          word_to_lower(a_path);
          word_to_lower(b_path);
          return a_path < b_path;
        });
      }
    private:
      fs::path get_filename(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).path.filename();
        else
          return std::get<FileDirInfos::FileInfos>(i).path.filename();
      };
  };
} // namespace Sorter
