#include <Controller.hpp>

#include <sorters/alpha.hpp>
#include <sorters/default.hpp>
#include <sorters/extension.hpp>
#include <sorters/separate_files_folders.hpp>
#include <sorters/size.hpp>

Controller::Controller(const model::Options &options) : m_options(options) {
  // Sorters
  if (options.sorters.empty())
    this->m_sort.emplace_back(new Sorter::Default());
  else
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
}

std::vector<FileDirInfos::DirInfos> Controller::create_models() {
  std::vector<FileDirInfos::DirInfos> models;
  models.reserve(this->m_options.paths.size());
  for (auto path : this->m_options.paths) {
    models.emplace_back(fs::directory_entry(fs::canonical((std::string)path)), this->m_options.hidden);
    for (auto &sorter : this->m_sort)
      sorter->sort(models.back().items);
  }
  return models;
}
