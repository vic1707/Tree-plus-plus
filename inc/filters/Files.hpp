#pragma once
/* std */
#include <string>
/* custom */
#include <displayers_specs/Filter.hpp>
#include <variant>

namespace Filter {
  class Files : public AFilter {
    public:
      /* Methods */
      void filter(FileDirInfos::DirInfos &parent) final {
        for (auto it = parent.items.begin(); it != parent.items.end(); ++it) {
          if (std::holds_alternative<FileDirInfos::DirInfos>(*it)) continue;
          remove_from_parent(it, parent);
          --it;
        }
      }
  };
} // namespace Filter
