#pragma once
/* std */
#include <filesystem>
#include <vector>
#include <variant>
/* fmt */
#include <fmt/format.h>
/* custom */
#include "size_unit.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

namespace FileDirInfos {
  struct NameInfos {
    /* Members */
    std::string filename;
    std::string extension;
    /* Constructors */
    NameInfos() noexcept = default;
    NameInfos(const fs::path &path) : filename(path.filename().string()), extension(path.extension().string()) {}
  };

  struct ItemInfos {
    /* Members */
    fs::path path;
    time_t time;
    NameInfos name;
    SizeUnit::SizeUnit size;
    /* Constructors */
    ItemInfos() noexcept = default;
    ItemInfos(const fs::directory_entry &entry) noexcept;
  };

  struct FileInfos : ItemInfos {
    /* Constructors */
    FileInfos() noexcept = default;
    FileInfos(const fs::directory_entry &entry) noexcept : ItemInfos(entry) {}
  };

  struct ItemsCount {
    /* Members */
    size_t dirs = 0;
    size_t files = 0;
  };

  struct ChildCount {
    /* Members */
    ItemsCount local;
    ItemsCount total;
    /* Operators */
    friend inline std::ostream &operator<<(std::ostream &os, const ChildCount &children) noexcept {
      if (children.total.dirs == 0 && children.total.files == 0) return os << "Empty directory";
      auto const dirs_plural = children.local.dirs == 1 ? "y" : "ies";
      auto const files_plural = children.local.files == 1 ? "" : "s";
      auto const total_dirs = children.local.dirs != children.total.dirs ? fmt::format(" ({} total)", children.total.dirs) : "";
      auto const total_files = children.local.files != children.total.files ? fmt::format(" ({} total)", children.total.files) : "";
      return os << children.local.dirs << " director" << dirs_plural << total_dirs << ", " << children.local.files << " file" << files_plural << total_files;
    }
  };

  struct DirInfos;
  template <typename T>
  concept Item = std::same_as<T, FileInfos> || std::same_as<T, DirInfos>;

  struct DirInfos : ItemInfos {
    /* Members */
    ChildCount children;
    std::vector<std::variant<DirInfos, FileInfos>> items;
    /* Constructors */
    DirInfos() noexcept = default;
    DirInfos(const fs::directory_entry &entry, bool &hidden) noexcept;
    /* Methods */
    template <typename Item>
    inline void push_item(const fs::directory_entry &entry, bool &hidden) noexcept;
  };

} // namespace FileDirInfos
