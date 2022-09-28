#pragma once
/* std */
#include <variant>
#include <vector>
/* custom */
#include <FileDirInfos.hpp>

using Items = std::vector<std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>>;
namespace Filter {
  class AFilter {
    private:
      /* Members */
      std::vector<std::string> m_discriminants;
    public:
      /* Destructor */
      virtual ~AFilter() = default;
      /* Members */
      virtual void filter(Items &items) = 0;
  };
} // namespace Filter
