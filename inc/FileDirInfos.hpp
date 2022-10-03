#pragma once
/* std */
#include <filesystem>
#include <variant>
#include <vector>
/* fmt */
#include <fmt/format.h>
/* custom */
namespace Sorter {class ASorter;} // #include "displayers_specs/Sorter.hpp"
namespace Filter {class AFilter;} // #include "displayers_specs/Filter.hpp"
#include "SizeUnit.hpp"
#include "Utils.hpp"

namespace fs = std::filesystem;

namespace FileDirInfos {
  struct ItemInfos {
    /* Members */
    fs::path path;
    time_t time;
    std::string name;
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

  struct DirInfos;
  template <typename T>
  concept Item = std::same_as<T, FileInfos> || std::same_as<T, DirInfos>;

  struct ChildCount {
    /* Members */
    ItemsCount local;
    ItemsCount total;
    /* Operators */
    friend inline std::ostream &operator<<(std::ostream &os, const ChildCount &children) {
      if (children.total.dirs == 0 && children.total.files == 0) return os << "Empty directory";
      auto const dirs_plural = children.local.dirs > 1 ? "ies" : "y";
      auto const files_plural = children.local.files > 1 ? "s" : "";
      auto const total_dirs = children.local.dirs != children.total.dirs ? fmt::format(" ({} total)", children.total.dirs) : std::string();
      auto const total_files = children.local.files != children.total.files ? fmt::format(" ({} total)", children.total.files) : std::string();
      auto result = fmt::format("{} director{}{} and {} file{}{}", children.local.dirs, dirs_plural, total_dirs, children.local.files, files_plural, total_files);
      return os << result;
    }
    /* Methods */
    void add_file() noexcept;
    void remove_file() noexcept;
    void add_dir(const DirInfos& dir) noexcept;
    void remove_dir(const DirInfos& dir) noexcept;
  };

  struct DirInfos : ItemInfos {
    /* Members */
    ChildCount children;
    std::vector<std::variant<DirInfos, FileInfos>> items;
    /* Constructors */
    DirInfos() noexcept = default;
    DirInfos(fs::directory_entry entry, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters, const std::vector<std::unique_ptr<Filter::AFilter>> &filters);
    /* Methods */
    template <Item T>
    inline std::variant<DirInfos, FileInfos> build_item(fs::directory_entry entry, const std::vector<std::unique_ptr<Sorter::ASorter>> &sorters, const std::vector<std::unique_ptr<Filter::AFilter>> &filters);
  };

} // namespace FileDirInfos

template <> struct fmt::formatter<FileDirInfos::ChildCount> {
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const FileDirInfos::ChildCount& p, FormatContext& ctx) const -> decltype(ctx.out()) {
      if (p.total.dirs == 0 && p.total.files == 0) return fmt::format_to(ctx.out(), "{}", "Empty directory");
      auto const dirs_plural = p.local.dirs > 1 ? "ies" : "y";
      auto const files_plural = p.local.files > 1 ? "s" : "";
      auto const total_dirs = p.local.dirs != p.total.dirs ? fmt::format(" ({} total)", p.total.dirs) : std::string();
      auto const total_files = p.local.files != p.total.files ? fmt::format(" ({} total)", p.total.files) : std::string();
      return fmt::format_to(ctx.out(), "{} director{}{} and {} file{}{}", p.local.dirs, dirs_plural, total_dirs, p.local.files, files_plural, total_files);
  }
};
