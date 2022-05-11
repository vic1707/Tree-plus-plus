#include "utils.hpp"

const std::array<std::string_view, 6> utils::sizes = {"B", "KB", "MB", "GB", "TB", "PB"};

utils::size_unit utils::readable_file_size(size_t size_byte) {
  size_t index = 0;
  while (size_byte > 1024) {
    size_byte /= 1024;
    index++;
  }
  // is missing floating point number
  return {size_byte, &sizes[index]};
}

utils::size_unit utils::readable_dir_size(fs::directory_entry path) {
  size_t size = 0;
  for (fs::recursive_directory_iterator it(path); it != fs::recursive_directory_iterator(); ++it) {
    if (!fs::is_directory(*it)) {
      size += fs::file_size(*it);
    }
  }
  return readable_file_size(size);
}