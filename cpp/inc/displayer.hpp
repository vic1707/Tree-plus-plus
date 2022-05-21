#ifndef DISPLAYER_HPP
  #define DISPLAYER_HPP
  /* custom */
  #include "file_dir_infos.hpp"

  // const std::array<std::string_view, 2> continuity_pointers;
  // const std::array<std::string_view, 2> entry_pointers;

  using Item = std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>;
  class Displayer {
    private:
      /* Methods */
      virtual void display_file(const FileDirInfos::FileInfos *item) noexcept = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item) noexcept = 0;
    
    protected:
      /* Members */
      size_t tab_size;

    public:
      /* Methods */
      virtual void display(const Item &item) noexcept = 0;
      /* Constructors */
      Displayer(size_t tab_size = 2) noexcept : tab_size(tab_size) {};
  };

#endif // DISPLAYER_HPP
