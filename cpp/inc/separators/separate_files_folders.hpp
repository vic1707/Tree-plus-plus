#ifndef FILE_FOLDER_SEPARATOR_HPP
  #define FILE_FOLDER_SEPARATOR_HPP
  /* custom */
  #include "displayers_specs/separator.hpp"

  namespace Separator {
    template <class First, class Second>
    class FileFolder : public ASeparator {
      public:
        void separate(Items &items) final override {
          std::stable_partition(items.begin(), items.end(), [](const auto &item) {
            return std::holds_alternative<First>(item);
          });
        };
    };
  } // namespace Separator
#endif // FILE_FOLDER_SEPARATOR_HPP
