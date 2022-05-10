#ifndef TREE_HPP
  #define TREE_HPP
  #include <array>
  #include <filesystem>
  #include <iostream>
  #include <string>
  // #include <string_view>
  #include <vector>
  #include "utils.hpp"

  namespace fs = std::filesystem;

  class Tree
  {

    private:
      /* Static */
      static const std::array<std::string, 2> inner_pointers;
      static const std::array<std::string, 2> final_pointers;
      /* Members */
      size_t dirs = 0;
      size_t files = 0;
      utils::size_unit size;
      /* Methods */
      inline void summary();
      inline void display_child_dir(fs::directory_entry dir, std::string prefix);
      void display_child_file(fs::directory_entry file, std::string prefix);
      void traverse(fs::directory_entry path, std::string prefix);

    public:
      Tree(char* path);
      ~Tree();
  };

#endif
