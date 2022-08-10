#pragma once
/* std */
#include <variant>
#include <vector>
/* custom */
#include <FileDirInfos.hpp>

using Items = std::vector<std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>>;
namespace Sorter {
  class ASorter {
    public:
      /* Destructor */
      virtual ~ASorter() = default;
      /* Members */
      virtual void sort(Items &items) = 0;
  };
} // namespace Sorter
