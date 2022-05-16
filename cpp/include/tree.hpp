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


      // const std::array<std::string_view, 2> continuity_pointers;
      // const std::array<std::string_view, 2> entry_pointers;


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
  class  Tree {
      DirInfo root;
    public:
       Tree(std::string_view path);
      ~ Tree() = default;

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
