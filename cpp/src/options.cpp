/* std */
#include <filesystem>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
/* custom */
#include <Options.hpp>

namespace fs = std::filesystem;

#ifndef _WIN32
  size_t get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (w.ws_col == 0) return 150;
    return w.ws_col;
  }
#else 
  size_t get_terminal_width() {
    return 150;
  }
#endif

namespace model {
  Options::Options() :
    paths(),
    sorters(),
    formatter(),
    indenter(),
    columns(get_terminal_width()),
    tab_size(2),
    redirect(false),
    hidden(false),
    size_in_bytes(false)
  {}

  void Options::parse_args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
      auto argv_sv = std::string_view(argv[i]);
      if (argv_sv == "-h" || argv_sv == "--help") {
        std::cout << "Usage: ./tree [-h|--help] [-a|--all-files] [-f|--foldable] [-r|--redirect] [--dirs-first|--files-first] [path(s)]\n";
        exit(0);
      }
      else if (argv_sv == "-a" || argv_sv == "--all-files")
        this->hidden = true;
      else if ( argv_sv == "--size-in-bytes")
        this->size_in_bytes = true;
      else if (argv_sv == "-r" || argv_sv == "--redirect")
        this->redirect = true;
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
      else if (fs::is_directory(argv_sv))
        this->paths.insert(argv_sv);
      else
        std::cerr << "Error: '" << argv_sv << "' is not a directory.\n";
    }
    if (this->paths.empty())
      this->paths.insert(".");
  }
} // namespace CLI
