#ifndef ALPHABETICAL_SORTER_HPP
  #define ALPHABETICAL_SORTER_HPP
  /* custom */
  #include "displayers_specs/sorter.hpp"

  namespace Sorter {
    class Alpha : public ASorter {
      void sort(Items &items) noexcept {
        std::sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
          if (std::holds_alternative<FileDirInfos::DirInfos>(a) && std::holds_alternative<FileDirInfos::DirInfos>(b)) {
              return std::get<FileDirInfos::DirInfos>(a).path.filename().string() < std::get<FileDirInfos::DirInfos>(b).path.filename().string();
          } else if (std::holds_alternative<FileDirInfos::FileInfos>(a) && std::holds_alternative<FileDirInfos::FileInfos>(b)) {
              return std::get<FileDirInfos::FileInfos>(a).path.filename().string() < std::get<FileDirInfos::FileInfos>(b).path.filename().string();
          } else if (std::holds_alternative<FileDirInfos::DirInfos>(a) && std::holds_alternative<FileDirInfos::FileInfos>(b)) {
              return std::get<FileDirInfos::DirInfos>(a).path.filename().string() < std::get<FileDirInfos::FileInfos>(b).path.filename().string();
          } else if (std::holds_alternative<FileDirInfos::FileInfos>(a) && std::holds_alternative<FileDirInfos::DirInfos>(b)) {
              return std::get<FileDirInfos::FileInfos>(a).path.filename().string() < std::get<FileDirInfos::DirInfos>(b).path.filename().string();
          } else {
              return false;
          }
        });
      }
    };
  } // namespace Sorter
#endif // ALPHABETICAL_SORTER_HPP
