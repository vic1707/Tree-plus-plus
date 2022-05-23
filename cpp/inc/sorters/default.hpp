#ifndef DEFAULT_SORTER_HPP
  #define DEFAULT_SORTER_HPP
  /* custom */
  #include "displayers_specs/sorter.hpp"

  namespace Sorter {
    class Default : public ASorter {
      void sort(Items &) noexcept override {}
    };
  } // namespace Sorter
#endif // DEFAULT_SORTER_HPP
