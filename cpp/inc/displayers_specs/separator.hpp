#ifndef SEPARATOR_HPP
  #define SEPARATOR_HPP
  /* std */
  #include <variant>
  #include <vector>
  /* custom */
  #include "file_dir_infos.hpp"

  using Items = std::vector<std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>>;
  namespace Separator {
    class ASeparator {
      public:
        /* Destructor */
        virtual ~ASeparator() = default;
        /* Members */
        virtual void separate(Items &items) = 0;
    };
  } // namespace Separator
#endif // SEPARATOR_HPP
