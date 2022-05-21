#ifndef CLASSIC_DISPLAYER_HPP
  #define CLASSIC_DISPLAYER_HPP
  /* std */
  #include <iostream>
  /* custom */
  #include "displayer.hpp"

  class Classic : public Displayer {
    private:
      /* Methods */
      void display_file(const FileDirInfos::FileInfos *item) noexcept override;
      void display_folder(const FileDirInfos::DirInfos *item) noexcept override;

    public:
      /* Methods */
      void display(const Item &item) noexcept override;
  };
#endif // CLASSIC_DISPLAYER_HPP