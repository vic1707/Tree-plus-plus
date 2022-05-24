#ifndef FILE_DIR_INFOS_HPP
  #define FILE_DIR_INFOS_HPP
  /* std */
  #include <filesystem>
  #include <vector>
  #include <variant>
  /* custom */
  #include "size_unit.hpp"
  #include "utils.hpp"

  namespace fs = std::filesystem;

  namespace FileDirInfos {
    struct ItemInfos {
      /* Members */
      fs::path path;
      SizeUnit::SizeUnit size;
      time_t time;
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
#endif // FILE_DIR_INFOS_HPP
