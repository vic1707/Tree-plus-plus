#pragma once
/* std */
#include <filesystem>
#include <vector>
#include <variant>
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

  struct DirInfos;
  template <typename T>
  concept Item = std::same_as<T, FileInfos> || std::same_as<T, DirInfos>;

  struct DirInfos : ItemInfos {
    /* Members */
    ItemsCount child_count;
    ItemsCount total_child_count;
    std::vector<std::variant<DirInfos, FileInfos>> items;
    /* Constructors */
    DirInfos() noexcept = default;
    DirInfos(const fs::directory_entry &entry, bool &hidden) noexcept;
    /* Methods */
    template <typename Item>
    inline void push_item(const fs::directory_entry &entry, bool &hidden) noexcept;
  };

} // namespace FileDirInfos
