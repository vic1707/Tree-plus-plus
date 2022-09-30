#pragma once
/* std */
#include <string>
/* custom */
#include <displayers_specs/Filter.hpp>
#include <variant>

namespace Filter {
  class Extensions : public AFilter {
    public:
      /* Constructors */
      Extensions(const std::unordered_set<std::string_view> &d): AFilter(d) {};
      /* Methods */
      void filter(FileDirInfos::DirInfos &parent) final {
        for (auto it = parent.items.begin(); it != parent.items.end(); ++it) {
          if (std::holds_alternative<FileDirInfos::DirInfos>(*it)) continue;
          auto &ext = std::get<FileDirInfos::FileInfos>(*it).name.extension;
          // if the extension isn't empty, remove the dot
          ext = ext.empty() ? ext : ext.substr(1);
          if (m_discriminants.find(ext) == m_discriminants.end()) continue;
          remove_from_parent(it, parent);
          --it;
        }
      }
  };
} // namespace Filter
