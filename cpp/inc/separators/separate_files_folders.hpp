#ifndef FILE_FOLDER_SEPARATOR_HPP
  #define FILE_FOLDER_SEPARATOR_HPP
  /* custom */
  #include "displayers_specs/separator.hpp"

  namespace Separator {
    template<class First, class Second>
    class FileFolder : public ASeparator {
      private:
        template <class T>
        auto compare() {
          return [](const auto& a, const auto& b) { return std::get<T>(a).path < std::get<T>(b).path; };
        }

      public:
        void separate(Items &items) final override {
          auto middle_part = std::partition(items.begin(), items.end(), [](const auto &item) {
            return std::holds_alternative<First>(item);
          });
          std::sort(items.begin(), middle_part, compare<First>());
          std::sort(middle_part, items.end(), compare<Second>());
        }
    };
  } // namespace Separator
#endif // FILE_FOLDER_SEPARATOR_HPP
