#pragma once
/* custom */
#include "displayers_specs/indenter.hpp"

namespace Indenter {
  class Fancy : public IndenterOptions {
    public:
      /* Constructors */
      Fancy(size_t tab_size = 2) : IndenterOptions("│", "─", "├", "└", tab_size) {}
  };
} // namespace Indenter
