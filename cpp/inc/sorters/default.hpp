#pragma once
/* custom */
#include "displayers_specs/sorter.hpp"

namespace Sorter {
  class Default : public ASorter {
    public:
      void sort(Items &) noexcept override {}
  };
} // namespace Sorter
