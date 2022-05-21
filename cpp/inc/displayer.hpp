#ifndef DISPLAYER_HPP
  #define DISPLAYER_HPP
  /* std */
  #include <string>
  /* custom */
  #include "file_dir_infos.hpp"

  // const std::array<std::string_view, 2> continuity_pointers;
  // const std::array<std::string_view, 2> entry_pointers;

  using Item = std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>;
  class Displayer {
    protected:
      /* Members */
      size_t tab_size;

    public:
      /* Methods */
      virtual void display(const Item &item, std::string prefix = "") noexcept = 0;
      static Displayer *get_Displayer();
      static Displayer *get_Displayer(auto ...args);
      /* Constructors */
      Displayer(size_t tab_size) noexcept : tab_size(tab_size) {};
  };

  class EntryDisplayer {
    private:
      /* Methods */
      virtual void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept = 0;
  };

#endif // DISPLAYER_HPP
