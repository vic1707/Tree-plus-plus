#ifndef FANCY_INDENTER_HPP
  #define FANCY_INDENTER_HPP
  /* custom */
  #include "indenter.hpp"

  namespace Indenter {
    class Fancy : public AIndenter {
      public:
        /* Constructors */
        Fancy(size_t tab_size = 2) : AIndenter("│", "─", "├", "└", tab_size) {}
    };
  } // namespace Indenter

#endif // FANCY_INDENTER_HPP
