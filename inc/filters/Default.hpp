#pragma once
/* custom */
#include <displayers_specs/Filter.hpp>

namespace Filter {
  class Default : public AFilter {
    public:
      constexpr void filter(Items &) noexcept final {}
  };
} // namespace Sorter
