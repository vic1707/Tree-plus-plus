#ifndef DEFAULT_SEPARATOR_HPP
  #define DEFAULT_SEPARATOR_HPP
  /* custom */
  #include "displayers_specs/separator.hpp"
  #include "file_dir_infos.hpp"

  namespace Separator {
    class Default : public ASeparator {
      public:
        void separate(Items &items) final override {}
    };
  } // namespace Separator
#endif // DEFAULT_SEPARATOR_HPP