#define DEFAULT_COLUMN_WIDTH 200

/* std */
#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

/* custom */
#include <Options.hpp>
#include <size/size.hpp>
#include <Utils.hpp>

#include <displayers_specs/Filter.hpp>
bool Filter::AFilter::keepSize = false;

namespace fs = std::filesystem;

#ifndef _WIN32
  #include <sys/ioctl.h>
  #include <unistd.h>
  size_t get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (w.ws_col == 0) return DEFAULT_COLUMN_WIDTH;
    return w.ws_col;
  }
#else
  size_t get_terminal_width() {
    return DEFAULT_COLUMN_WIDTH;
  }
#endif

namespace model {
  Options::Options() :
    paths(),
    sorters(),
    filters(
      { {"hidden", {}} }
    ),
    formatter(),
    indenter(),
    columns(get_terminal_width()),
    tab_size(2),
    redirect(false)
  {}

  void Options::parse_args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
      auto argv_sv = std::string_view(argv[i]);
      if (argv_sv == "-h" || argv_sv == "--help") {
        std::cout << "Usage: ./tree [-h|--help] [-a|--all-files] [-f|--foldable] [-r|--redirect] [--dirs-first|--files-first] [path(s)]\n";
        exit(0);
      }
      else if (argv_sv == "-a" || argv_sv == "--all-files")
        this->filters.erase("hidden");
      else if ( argv_sv == "--size-in-bytes")
        SizeUnit::size_in_bytes = true;
      else if (argv_sv == "-r" || argv_sv == "--redirect") {
        this->redirect = true;
        this->columns = DEFAULT_COLUMN_WIDTH;
      }
      else if (argv_sv.starts_with("--column="))
        this->columns = std::stoi(std::string(argv[i]).substr(9));
      else if (argv_sv.starts_with("--tab-size=")) {
        int t = std::stoi((std::string)argv_sv.substr(11));
        if (t < 2)
          std::cerr << "Error: " << "tab_size must be >= 2\n";
        else
          this->tab_size = t;
      } else if (argv_sv.starts_with("--sort-by="))
        this->sorters.insert(argv_sv.substr(10));
      else if (argv_sv.starts_with("--indenter="))
        this->indenter = argv_sv.substr(11);
      else if (argv_sv.starts_with("--formatter="))
        this->formatter = argv_sv.substr(12);
      else if (argv_sv.starts_with("--keep-size"))
        Filter::AFilter::keepSize = true;
      else if (argv_sv.starts_with("--filter-by=")) {
        auto filter = argv_sv.substr(12);
        auto filter_options = Utils::split<std::vector<std::string_view>>(filter, '_');
        this->filters[filter_options.at(0)] = filter_options.size() > 1
          ? Utils::split<std::unordered_set<std::string_view>>(filter_options[1], ',')
          : std::unordered_set<std::string_view>{};
      }
      else if (fs::is_directory(argv_sv))
        this->paths.insert(argv_sv);
      else
        std::cerr << "Error: '" << argv_sv << "' is not a directory.\n";
    }
    if (this->paths.empty())
      this->paths.insert(".");
  }
} // namespace CLI
