#ifndef ALPHABETICAL_SORTER_HPP
  #define ALPHABETICAL_SORTER_HPP
  /* std */
  #include <string>
  /* custom */
  #include "displayers_specs/sorter.hpp"

  namespace Sorter {
    class Alpha : public ASorter {
      void sort(Items &items) noexcept {
        std::sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
          auto get_filename = [](const auto& a) -> std::string {
            if (std::holds_alternative<FileDirInfos::DirInfos>(a))
              return std::get<FileDirInfos::DirInfos>(a).path.filename().string();
            else
              return std::get<FileDirInfos::FileInfos>(a).path.filename().string();
          };
          return get_filename(a) < get_filename(b);
        });
      }
    };
  } // namespace Sorter
#endif // ALPHABETICAL_SORTER_HPP
