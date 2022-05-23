#ifndef SPACE_INDENTER_HPP
  #define SPACE_INDENTER_HPP
  /* custom */
  #include "displayers_specs/indenter.hpp"

  namespace Indenter {
    class Space : public IndenterOptions {
      public:
        /* Constructors */
        Space(size_t tab_size = 2) : IndenterOptions(" ", " ", " ", " ", tab_size) {}
    };
  } // namespace Indenter

#endif // SPACE_INDENTER_HPP
