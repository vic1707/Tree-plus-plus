#pragma once
/* std */
#include <filesystem>
#include <string>
#include <string_view>
/* custom */
#include "args.hpp"
#include "file_dir_infos.hpp"

namespace fs = std::filesystem;

class Tree {
  private:
    /* Members */
    FileDirInfos::DirInfos root;

  public:
    /* Constructors */
    Tree(std::string_view path) noexcept : root(fs::directory_entry(fs::canonical((std::string)path))) {};
    ~Tree() noexcept = default;
    /* Methods */
    FileDirInfos::DirInfos &get_root() noexcept { return root; }
};
