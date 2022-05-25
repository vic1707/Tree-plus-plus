#ifndef EXTENSION_SORTER_HPP
  #define EXTENSION_SORTER_HPP
  /* std */
  #include <set>
  /* custom */
  #include "displayers_specs/sorter.hpp"

  namespace Sorter {
    class Extension : public ASorter {
      public:
        void sort(Items &items) final override {
          // separate files and folders
          Items::iterator files = std::stable_partition(items.begin(), items.end(), [](const auto &item) {
            return std::holds_alternative<FileDirInfos::FileInfos>(item);
          });

          // make a set with all extensions in the files
          std::set<std::string> extensions;
          for (auto it = items.begin(); it != files; ++it)
            extensions.insert(std::get<FileDirInfos::FileInfos>(*it).name.extension);

          // separate the files by their extensions
          for (const auto &ext : extensions)
            std::stable_partition(items.begin(), files, [&ext](const auto &item) {
              return std::get<FileDirInfos::FileInfos>(item).name.extension != ext;
            });
        };
    };
  } // namespace Sorter
#endif
