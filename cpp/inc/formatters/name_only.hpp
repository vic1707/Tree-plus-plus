#ifndef NAME_ONLY_FORMATTER_HPP
  #define NAME_ONLY_FORMATTER_HPP
  /* std */
  #include <iostream>
  #include <string>
  /* custom */
  #include "displayers_specs/formatter.hpp"
  #include "file_dir_infos.hpp"

  namespace Formatter {
    class NameOnly : public AFormatter {
      void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept override {
        std::cout << prefix << item->path.filename().string() << "\n";
      }

      void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept override {
        std::cout << prefix << item->path.filename().string() << "\n";
      }
    };
  } // namespace Formatter
#endif // NAME_ONLY_FORMATTER_HPP
