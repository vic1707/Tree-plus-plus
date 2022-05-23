#ifndef DISPLAYERS_HPP
  #define DISPLAYERS_HPP
  /* std */
  #include <string>
  #include <string_view>
  /* custom */
  // specs
  #include "displayers_specs/indenter.hpp"
  #include "displayers_specs/formatter.hpp"
  // models
  #include "displayers_specs/name_only.formatter.hpp"
  #include "displayers_specs/full_infos.formatter.hpp"

  class Classic : public NameOnly, public Indenter {
    public:
      /* Constructors */
      Classic(size_t tab_size = 2) : Indenter("│", "─", "├", "└", tab_size) {}
  };
#endif // DISPLAYERS_HPP
