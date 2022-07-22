#pragma once
/* custom */
#include "displayers_specs/Sorter.hpp"
#include "Options.hpp"

class Controller {
  private:
    /* Members */
    std::vector<std::unique_ptr<Sorter::ASorter>> m_sort;
    const model::Options &m_options;
  
  public:
    /* Constructors */
    Controller(const model::Options &options);
    /* Methods */
    std::vector<FileDirInfos::DirInfos> create_models();
};
