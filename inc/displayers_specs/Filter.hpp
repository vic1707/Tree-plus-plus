#pragma once
/* std */
#include <string_view>
#include <unordered_set>
#include <variant>
#include <vector>
/* custom */
#include <FileDirInfos.hpp>
#include <size/size.hpp>

namespace Filter {
  class AFilter {
    private:
      size::Size get_size(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).size;
        else
          return std::get<FileDirInfos::FileInfos>(i).size;
      };
    protected:
      /* Members */
      std::unordered_set<std::string_view> m_discriminants;
      /* Destructor */
      AFilter() = default;
      AFilter(const std::unordered_set<std::string_view> &d): m_discriminants(d) {};
      /* Methods */
      void remove_from_parent(std::vector<std::variant<FileDirInfos::DirInfos, FileDirInfos::FileInfos>>::iterator i, FileDirInfos::DirInfos &p) {
        if (std::holds_alternative<FileDirInfos::FileInfos>(*i)) {
          p.children.remove_file();
          if (!keepSize) p.size -= std::get<FileDirInfos::FileInfos>(*i).size;
        } else {
          const auto dir = std::get<FileDirInfos::DirInfos>(*i);
          p.children.remove_dir(dir);
          if (!keepSize) p.size -= dir.size;
        }
        p.items.erase(i);
      }
    public:
      static bool keepSize;
      /* Destructor */
      virtual ~AFilter() = default;
      /* Members */
      virtual void filter(FileDirInfos::DirInfos &parent) = 0;
  };
} // namespace Filter
