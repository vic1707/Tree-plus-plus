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
    FileInfos(const fs::directory_entry &entry) noexcept : ItemInfos(entry) {}
  };

  struct DirInfos : ItemInfos {
    /* Members */
    std::vector<std::variant<DirInfos, FileInfos>> items;
    /* Constructors */
    DirInfos(const fs::directory_entry &entry) noexcept;
  };

  template <typename T>
  concept Item = std::same_as<T, FileDirInfos::FileInfos> || std::same_as<T, FileDirInfos::DirInfos>;

  template <typename Item>
  inline constexpr void push_item(auto &self, const fs::directory_entry &entry) noexcept;
} // namespace FileDirInfos
