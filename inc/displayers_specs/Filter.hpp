#pragma once
/* std */
#include <string_view>
#include <unordered_set>
#include <variant>
#include <vector>
/* custom */
#include <FileDirInfos.hpp>

using Items = std::vector<std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>>;
namespace Filter {
  class AFilter {
    private:
      /* Members */
      std::unordered_set<std::string_view> m_discriminants;
    public:
      /* Destructor */
      virtual ~AFilter() = default;
      /* Members */
      virtual void filter(Items &items) = 0;
  };
} // namespace Filter
