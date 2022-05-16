#ifndef TREE_HPP
  #define TREE_HPP
  #include <array>
  #include <filesystem>
  #include <iostream>
  #include <string>
  #include <string_view>
  #include <vector>
  #include "args.hpp"
  #include "fs_utils.hpp"

  namespace fs = std::filesystem;

  class Tree
  {
    private:
      /* Static */
      static const std::array<std::string_view, 2> continuity_pointers;
      static const std::array<std::string_view, 2> entry_pointers;
      /* Members */
      std::string_view continuity_pointer;
      size_t dirs = 0;
      size_t files = 0;
      arguments::options options;
      std::string path;
      fs_utils::size_unit size;
      /* Methods */
      void display_child_dir(fs::directory_entry dir, std::string prefix);
      void display_child_file(fs::directory_entry file, std::string prefix);
      inline void summary() {
        std::cout << "\n" << dirs << " directories, " << files << " files - size: " << size.size << *size.unit << ".\n";
      };
      void traverse(fs::directory_entry path, std::string prefix);

    public:
      Tree(std::string_view path, arguments::options opt);
      ~Tree() = default;
  };

#endif
