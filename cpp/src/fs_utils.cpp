#include "fs_utils.hpp"

namespace fs_utils {
  const std::array<std::string_view, 6> sizes = {"B", "KB", "MB", "GB", "TB", "PB"};

  SizeUnit::SizeUnit(size_t bytes) noexcept : bytes(bytes) {
    reload_unit();
  }
  void SizeUnit::reload_unit() {
    auto sizes_it = sizes.begin();
    size_t ratio_num = 1;
    for (size_t ratio_bytes = bytes; ratio_bytes > 1024; ratio_bytes /= 1024, ratio_num*=1024, ++sizes_it);
    unit = Unit{ 
      Ratio{ratio_num, 1}, 
      *sizes_it 
    };
  }
}
