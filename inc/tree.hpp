#ifndef TREE_HPP
  #define TREE_HPP
  #include <array>
  #include <filesystem>
  #include <iostream>
  #include <vector>
  #include "utils.hpp"

  namespace fs = std::filesystem;

  class Tree
  {

    private:
      /* Static */
      static const char* inner_pointers[2];
      static const char* final_pointers[2];
      /* Members */
      size_t dirs = 0;
      size_t files = 0;
      utils::size_unit size;
      /* Methods */
      inline void summary();
      inline void display_child_dir(fs::directory_entry dir, char* prefix);
      void display_child_file(fs::directory_entry file, char* prefix);
      void traverse(fs::directory_entry path, char* prefix);

    public:
      Tree(char* path);
      ~Tree();
  };

#endif
