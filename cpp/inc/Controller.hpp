#pragma once
#include "Options.hpp"
#include "displayers_specs/sorter.hpp"

class Controller {
  private:
    /* Members */
    std::vector<std::unique_ptr<Sorter::ASorter>> m_sort;
    const model::Options& m_options;
  
  public:
    /* Constructors */
    Controller(const model::Options& options);
    /* Methods */
    std::vector<FileDirInfos::DirInfos> create_models();
};
