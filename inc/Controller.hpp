#pragma once
/* std */
#include <vector>
/* custom */
#include "displayers_specs/Sorter.hpp"
#include "displayers_specs/Filter.hpp"
#include "Options.hpp"

class Controller {
  private:
    /* Members */
    std::vector<std::unique_ptr<Sorter::ASorter>> m_sort;
    std::vector<std::unique_ptr<Filter::AFilter>> m_filter;
    const model::Options &m_options;
  
  public:
    /* Constructors */
    Controller(const model::Options &options);
    /* Methods */
    std::vector<FileDirInfos::DirInfos> create_models();
};
