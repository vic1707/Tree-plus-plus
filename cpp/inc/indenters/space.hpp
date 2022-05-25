#pragma once
/* custom */
#include "displayers_specs/indenter.hpp"

namespace Indenter {
  class Space : public IndenterOptions {
    public:
      /* Constructors */
      Space(size_t tab_size = 2) : IndenterOptions(" ", " ", " ", " ", tab_size) {}
  };
} // namespace Indenter
