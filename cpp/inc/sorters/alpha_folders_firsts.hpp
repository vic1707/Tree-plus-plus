#ifndef ALPHA_FOLDERS_FIRSTS_SORTER_HPP
  #define ALPHA_FOLDERS_FIRSTS_SORTER_HPP
  /* custom */
  #include "displayers_specs/sorter.hpp"

  namespace Sorter {
    class AlphaFoldersFirsts : public ASorter {
      private:
        template <class T>
        auto compare() {
          return [](const auto& a, const auto& b) { return std::get<T>(a).path < std::get<T>(b).path; };
        }
      public:
        void sort(Items &items) final override {
          auto middle_part = std::partition(items.begin(), items.end(), [](const auto &item) {
            return std::holds_alternative<FileDirInfos::DirInfos>(item);
          });
          std::sort(items.begin(), middle_part, compare<FileDirInfos::DirInfos>());
          std::sort(middle_part, items.end(), compare<FileDirInfos::FileInfos>());
        }
    };
  }
#endif // ALPHA_FOLDERS_FIRSTS_SORTER_HPP
