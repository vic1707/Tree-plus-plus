#include <SizeUnit.hpp>

const std::array<std::string_view, 6> sizes = {"B", "KB", "MB", "GB", "TB", "PB"};

bool SizeUnit::size_in_bytes = false;

void SizeUnit::reload_unit() noexcept {
  auto sizes_it = sizes.begin();
  size_t ratio_num = 1;
  for (size_t ratio_bytes = bytes; ratio_bytes > 1024; ratio_bytes /= 1024, ratio_num *= 1024, ++sizes_it)
    ;
  unit = Unit(
    Ratio{ratio_num, 1},
    *sizes_it
  );
}
