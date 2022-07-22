#pragma once
/* custom */
#include <displayers_specs/Sorter.hpp>

namespace Sorter {
  class Default : public ASorter {
    public:
      constexpr void sort(Items &) noexcept final {}
  };
} // namespace Sorter
