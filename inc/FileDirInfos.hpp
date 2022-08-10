#pragma once
/* std */
#include <filesystem>
#include <variant>
#include <vector>
/* fmt */
#include <fmt/format.h>
/* custom */
namespace Sorter {class ASorter;} // #include "displayers_specs/Sorter.hpp"
#include "SizeUnit.hpp"
#include "Utils.hpp"

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
    SizeUnit size;
    /* Constructors */
    ItemInfos() noexcept = default;
    ItemInfos(fs::directory_entry entry);
  };

  struct FileInfos : ItemInfos {
    /* Constructors */
    FileInfos() noexcept = default;
    FileInfos(fs::directory_entry entry) : ItemInfos(entry) {}
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
    friend inline std::ostream &operator<<(std::ostream &os, const ChildCount &children) {
      if (children.total.dirs == 0 && children.total.files == 0) return os << "Empty directory";
      auto const dirs_plural = children.local.dirs < 1 ? "y" : "ies";
      auto const files_plural = children.local.files < 1 ? "" : "s";
      auto const total_dirs = children.local.dirs != children.total.dirs ? fmt::format(" ({} total)", children.total.dirs) : std::string();
      auto const total_files = children.local.files != children.total.files ? fmt::format(" ({} total)", children.total.files) : std::string();
      auto result = fmt::format("{} director{}{} and {} file{}{}", children.local.dirs, dirs_plural, total_dirs, children.local.files, files_plural, total_files);
      return os << result;
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
    DirInfos(fs::directory_entry entry, bool hidden, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters);
    /* Methods */
    template <typename Item>
    inline std::variant<DirInfos, FileInfos> build_item(fs::directory_entry entry, bool hidden, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters);
  };

} // namespace FileDirInfos
