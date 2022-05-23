#ifndef FORMATTER_HPP
  #define FORMATTER_HPP
  /* std */
  #include <iostream>
  #include <string>
  /* custom */
  #include "file_dir_infos.hpp"

  class Formatter {
    public:
      /* Methods */
      virtual void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept = 0;
  };
#endif // FORMATTER_HPP
