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
      virtual void display(const Item &item, size_t tab) noexcept = 0;
  };

  class Classic : public Displayer {
    public:
      /* Methods */
      void display(const Item &item, size_t tab) noexcept override;

    private:
      /* Methods */
      void display_info(const FileDirInfos::ItemInfos *info) noexcept;
  };
#endif // DISPLAYER_HPP
