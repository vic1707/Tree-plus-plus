#ifndef EXTENSION_SORTER_HPP
  #define EXTENSION_SORTER_HPP
  /* custom */
  #include "displayers_specs/sorter.hpp"

  namespace Sorter {
    class Extension : public ASorter {
      public:
        void sort(Items &items) noexcept {
          std::stable_sort(items.begin(), items.end(), [](const auto &a, const auto &b) {
            auto get_extension = [](const auto& a) -> std::string {
              if (std::holds_alternative<FileDirInfos::DirInfos>(a))
                return std::get<FileDirInfos::DirInfos>(a).name.extension;
              else
                return std::get<FileDirInfos::FileInfos>(a).name.extension;
            };
            return get_extension(a) < get_extension(b);
          });
        }
    };
  } // namespace Sorter
#endif // EXTENSION_SORTER_HPP
