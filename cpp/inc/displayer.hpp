#pragma once
/* std */
#include <string>
#include <string_view>
#include <unordered_set>
/* custom */
// displayers_specs
#include "displayers_specs/formatter.hpp"
#include "displayers_specs/indenter.hpp"
#include <Options.hpp>
#include <string_view>

namespace Displayer {

  class Displayer {
    private:
      /* Members */
      const model::Options& m_options;
      std::unique_ptr<Indenter::IndenterOptions> m_indent;
      std::unique_ptr<Formatter::AFormatter> m_format;
      std::ostream* m_stream;
      /* Methods */
      void display_dir(const FileDirInfos::DirInfos& dir_infos, std::string prefix = std::string());
      std::ostream& getStream() const {
        return *m_stream;
      }
      
    public:
      /* Constructors */
      Displayer(const model::Options& options);
      /* Methods */
      void display(const std::vector<FileDirInfos::DirInfos> &dirs);
  };
}
