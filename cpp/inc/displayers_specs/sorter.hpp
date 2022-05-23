#ifndef SORTER_HPP
  #define SORTER_HPP
  /* std */
  #include <variant>
  #include <vector>
  /* custom */
  #include "file_dir_infos.hpp"

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
#endif // SORTER_HPP
