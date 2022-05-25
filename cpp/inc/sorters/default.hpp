#pragma once
/* custom */
#include "displayers_specs/sorter.hpp"

namespace Sorter {
  class Default : public ASorter {
    void sort(Items &) noexcept override {}
  };
} // namespace Sorter
