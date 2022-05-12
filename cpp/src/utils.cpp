#include "utils.hpp"

const std::array<std::string_view, 6> utils::sizes = {"B", "KB", "MB", "GB", "TB", "PB"};

utils::size_unit utils::readable_file_size(float size_byte) {
  size_t index = 0;
  for (; size_byte > 1024.0; size_byte /= 1024.0, index++);
  return {((float)(int)(size_byte * 100)/100), &sizes[index]}; // two digits after decimal point
}

utils::size_unit utils::readable_dir_size(fs::directory_entry path) {
  size_t size = 0;
  for (fs::recursive_directory_iterator it(path); it != fs::recursive_directory_iterator(); ++it)
    if (!fs::is_directory(*it))
      size += fs::file_size(*it);
  return readable_file_size((float) size);
}
