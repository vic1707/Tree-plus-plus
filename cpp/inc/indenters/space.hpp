#ifndef SPACE_INDENTER_HPP
  #define SPACE_INDENTER_HPP
  /* custom */
  #include "displayers_specs/indenter.hpp"

  namespace Indenter {
    class Space : public AIndenter {
      public:
        /* Constructors */
        Space(size_t tab_size = 2) : AIndenter(" ", " ", " ", " ", tab_size) {}
    };
  } // namespace Indenter

#endif // SPACE_INDENTER_HPP
