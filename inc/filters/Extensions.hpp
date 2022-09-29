#pragma once
/* std */
#include <string>
/* custom */
#include <displayers_specs/Filter.hpp>

namespace Filter {
  class Extensions : public AFilter {
    public:
      /* Constructors */
      Extensions(const std::unordered_set<std::string_view> &d): AFilter(d) {};
      /* Methods */
      void filter(FileDirInfos::DirInfos &parent) final {
        for (auto it = parent.items.begin(); it != parent.items.end(); ++it) {
          if (std::find(m_discriminants.begin(), m_discriminants.end(), this->get_extension(*it)) != m_discriminants.end()) return;
          remove_from_parent(it, parent);
          --it;
        }
      }
    private:
      std::string get_extension(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).name.extension;
        else
          return std::get<FileDirInfos::FileInfos>(i).name.extension;
      };
  };
} // namespace Filter
