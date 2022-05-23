#ifndef NAME_ONLY_FORMATTER_HPP
  #define NAME_ONLY_FORMATTER_HPP
  /* std */
  #include <iostream>
  #include <string>
  /* custom */
  #include "displayers_specs/formatter.hpp"
  #include "file_dir_infos.hpp"

  class FullInfos : virtual public Formatter {
    void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept override {
      char buff[20];
      std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
      std::cout << prefix << item->path.filename().string() << " - " << item->size << " - " << buff << "\n";
    }

    void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept override {
      char buff[20];
      std::strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::localtime(&item->time));
      std::cout << prefix << item->path.filename().string() << " - " << item->size << " - " << buff << "\n";
    }
  };

#endif // NAME_ONLY_FORMATTER_HPP
