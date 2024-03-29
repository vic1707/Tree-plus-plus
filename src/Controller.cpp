#include <Controller.hpp>
/* Sorters */
#include <sorters/Alpha.hpp>
#include <sorters/Extension.hpp>
#include <sorters/Separate_files_folders.hpp>
#include <sorters/Size.hpp>
/* Filters */
#include <filters/Extensions.hpp>
#include <filters/Files.hpp>
#include <filters/Hidden.hpp>

Controller::Controller(const model::Options &options) : m_options(options) {
  // Sorters
  for (auto &opt : options.sorters)
    if (opt == "alpha")
      this->m_sort.emplace_back(new Sorter::Alpha());
    else if (opt == "extension")
      this->m_sort.emplace_back(new Sorter::Extension());
    else if (opt == "size")
      this->m_sort.emplace_back(new Sorter::Size());
    else if (opt == "files_folders")
      this->m_sort.emplace_back(new Sorter::SeparateFilesFolders<FileDirInfos::FileInfos>());
    else if (opt == "folders_files")
      this->m_sort.emplace_back(new Sorter::SeparateFilesFolders<FileDirInfos::DirInfos>());
  // Filters
  for (auto &opt : options.filters)
    if (opt.first == "ext")
      this->m_filter.emplace_back(new Filter::Extensions(opt.second));
    else if (opt.first == "hidden")
      this->m_filter.emplace_back(new Filter::Hidden());
    else if (opt.first == "files")
      this->m_filter.emplace_back(new Filter::Files());
}

std::vector<FileDirInfos::DirInfos> Controller::create_models() {
  std::vector<FileDirInfos::DirInfos> models;
  models.reserve(this->m_options.paths.size());
  for (auto path : this->m_options.paths) {
    FileDirInfos::DirInfos model(fs::directory_entry(fs::canonical((std::string)path)), this->m_sort, this->m_filter);
    models.emplace_back(model);
  }
  return models;
}
