#ifndef TREE_HPP
  #define TREE_HPP
  #include <array>
  #include <filesystem>
  #include <iostream>
  #include <string>
  #include <string_view>
  #include <vector>
  #include "args.hpp"
  #include "utils.hpp"

  namespace fs = std::filesystem;

  class Tree
  {

    private:
      /* Static */
      static const std::array<std::string_view, 2> continuity_pointers;
      static const std::array<std::string_view, 2> entry_pointers;
      /* Members */
      const std::string_view* continuity_pointer;
      size_t dirs = 0;
      size_t files = 0;
      arguments::options options;
      std::string path;
      utils::size_unit size;
      /* Methods */
      inline void display_child_dir(fs::directory_entry dir, std::string prefix);
      inline void display_child_file(fs::directory_entry file, std::string prefix);
      inline void summary();
      void traverse(fs::directory_entry path, std::string prefix);

    public:
      Tree(char* path, arguments::options opt);
      ~Tree();
  };

#endif
