#ifndef DISPLAYER_HPP
  #define DISPLAYER_HPP
  /* std */
  #include <iostream>
  #include <variant>
  /* custom */
  #include "file_dir_infos.hpp"

  // const std::array<std::string_view, 2> continuity_pointers;
  // const std::array<std::string_view, 2> entry_pointers;

  using Item = std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>;
  class Displayer {
    public:
      /* Methods */
      virtual void display(const Item &item) noexcept = 0;
    private:
      /* Methods */
      virtual void display_file(const FileDirInfos::FileInfos *item) noexcept = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item) noexcept = 0;
  };

  class Classic : public Displayer {
    public:
      /* Methods */
      void display(const Item &item) noexcept override;

    private:
      /* Methods */
      void display_file(const FileDirInfos::FileInfos *item) noexcept override;
      void display_folder(const FileDirInfos::DirInfos *item) noexcept override;
  };
#endif // DISPLAYER_HPP
