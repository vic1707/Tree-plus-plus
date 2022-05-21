#ifndef TREE_HPP
  #define TREE_HPP
  /* std */
  #include <filesystem>
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
      Tree(std::string_view path) noexcept : root(fs::directory_entry(path)){};
      ~Tree() noexcept = default;
      /* Methods */
      const FileDirInfos::DirInfos &get_root() const noexcept { return root; }
  };
#endif // TREE_HPP