#ifndef TREE_HPP
  #define TREE_HPP
  #include <array>
  #include <filesystem>
  #include <iostream>
  #include <string>
  #include <string_view>
  #include <vector>
  #include <variant>
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
      fs_utils::SizeUnit size;
      /* Methods */
      void display_child_dir(fs::directory_entry dir, std::string prefix);
      void display_child_file(fs::directory_entry file, std::string prefix);
      inline void summary() {
        std::cout << "\n" << dirs << " directories, " << files << " files - size: " << size << ".\n";
      };
      void traverse(fs::directory_entry path, std::string prefix);

    public:
      Tree(std::string_view path, arguments::options opt);
      ~Tree() = default;
  };



  struct ItemInfo {
    ItemInfo() = default;
    ItemInfo(const fs::directory_entry& entry);
    virtual void display(size_t) {}
    fs::path path;
    fs_utils::SizeUnit size;
    time_t time;
  };
  struct FileInfo : ItemInfo {
    FileInfo(const fs::directory_entry& entry);
  };
  struct DirInfo : ItemInfo {
    DirInfo(const fs::directory_entry& entry);
    std::vector<std::variant<DirInfo, FileInfo>> items;
  };

  using Item = std::variant<DirInfo, FileInfo>;
  class Tree2 {
      DirInfo root;
    public:
      Tree2(std::string_view path);
      ~Tree2() = default;

      const DirInfo& get_root() const { 
        return root; 
      }
  };

  class Displayer {
    public:
      virtual void display(const Item& item, size_t tab) = 0;
  };

  class Classic : public Displayer {
    public:
      void display(const Item& item, size_t tab) override;
    private:
      void display_info(const ItemInfo* info);
  };

  

#endif
