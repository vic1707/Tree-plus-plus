#ifndef CLASSIC_DISPLAYER_HPP
  #define CLASSIC_DISPLAYER_HPP
  /* std */
  #include <iostream>
  #include <string>
  /* custom */
  #include "displayer.hpp"

  class Classic : public Displayer, public EntryDisplayer {
    private:
      /* Methods */
      void display_file(const FileDirInfos::FileInfos *item, std::string prefix) noexcept override;
      void display_folder(const FileDirInfos::DirInfos *item, std::string prefix) noexcept override;

    public:
      /* Methods */
      void display(const Item &item, std::string prefix = "") noexcept override;
      /* Constructors */
      Classic(size_t tab_size = 2) noexcept : Displayer(tab_size) {};
  };
#endif // CLASSIC_DISPLAYER_HPP
