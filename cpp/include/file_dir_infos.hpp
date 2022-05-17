#ifndef FILE_DIR_INFOS_HPP
  #define FILE_DIR_INFOS_HPP
  /* std */
  #include <filesystem>
  #include <vector>
  #include <variant>
  /* custom */
  #include "size_unit.hpp"

  namespace fs = std::filesystem;

  namespace FileDirInfos {
    struct ItemInfos {
      /* Members */
      fs::path path;
      SizeUnit::SizeUnit size;
      time_t time;
      /* Constructors */
      ItemInfos() = default;
      ItemInfos(const fs::directory_entry &entry);
      /* Methods */
      virtual void display(size_t) {}
    };

    struct FileInfos : ItemInfos {
      /* Constructors */
      FileInfos(const fs::directory_entry &entry) : ItemInfos(entry) {}
    };
  
    struct DirInfos : ItemInfos {
      /* Members */
      std::vector<std::variant<DirInfos, FileInfos>> items;
      /* Constructors */
      DirInfos(const fs::directory_entry &entry);
    };

    inline void add_item(auto &self, const fs::directory_entry &entry);
  } // namespace FileDirInfos
#endif // FILE_DIR_INFOS_HPP