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

    struct NameInfos {
      /* Members */
      std::string filename;
      std::string extension;
      /* Constructors */
      NameInfos() noexcept = default;
      NameInfos(const fs::path &path) : filename(path.filename().string()), extension(path.extension().string()) {}
    };

    struct ItemInfos {
      /* Members */
      fs::path path;
      time_t time;
      NameInfos name;
      /* Constructors */
      ItemInfos() noexcept = default;
      ItemInfos(const fs::directory_entry &entry) noexcept;
    };

    struct FileInfos : ItemInfos {
      /* Members */
      SizeUnit::SizeUnit size;
      /* Constructors */
      FileInfos(const fs::directory_entry &entry) noexcept : ItemInfos(entry), size(fs::file_size(path)) {}
    };

    struct DirInfos : ItemInfos {
      /* Members */
      SizeUnit::SizeUnit size;
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
