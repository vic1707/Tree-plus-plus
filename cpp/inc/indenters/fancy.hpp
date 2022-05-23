#ifndef FANCY_INDENTER_HPP
  #define FANCY_INDENTER_HPP
  /* custom */
  #include "displayers_specs/indenter.hpp"

  namespace Indenter {
    class Fancy : public IndenterOptions {
      public:
        /* Constructors */
        Fancy(size_t tab_size = 2) : IndenterOptions("│", "─", "├", "└", tab_size) {}
    };
  } // namespace Indenter

#endif // FANCY_INDENTER_HPP
