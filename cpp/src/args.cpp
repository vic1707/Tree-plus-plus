#include "args.hpp"

namespace CLI {
  Arguments parse_args(int argc, char **argv) noexcept {
    Arguments args = Arguments{
      .opt = Options{false},
      .paths = {},
      .displayer_options = {
        .indenter = "space",
        .formatter = "full_infos",
        .sorters = {},
        .all_files = false,
        .tab_size = 2
      }
    };

    for (int i = 1; i < argc; i++) {
      auto argv_sv = std::string_view(argv[i]);
      if (argv_sv == "-h" || argv_sv == "--help") {
        std::cout << "Usage: ./tree [-h|--help] [-a|--all-files] [-f|--foldable] [-r|--redirect] [--dirs-first|--files-first] [path(s)]\n";
        exit(0);
      }
      else if (argv_sv == "-a" || argv_sv == "--all-files")
        args.displayer_options.all_files = true;
      else if (argv_sv == "-r" || argv_sv == "--redirect")
        args.opt.redirect = true;
      else if (argv_sv.starts_with("--tab_size=")) {
        int tab_size = std::stoi((std::string)argv_sv.substr(11));
        if (tab_size < 2)
          std::cerr << "Error: " << "tab_size must be >= 2\n";
        else
          args.displayer_options.tab_size = tab_size;
      } else if (fs::is_directory(argv_sv))
        args.paths.push_back(argv_sv);
      else if (argv_sv.starts_with("--sort-by="))
        args.displayer_options.sorters.insert(argv_sv.substr(10));
      else if (argv_sv.starts_with("--indenter="))
        args.displayer_options.indenter = argv_sv.substr(11);
      else if (argv_sv.starts_with("--formatter="))
        args.displayer_options.formatter = argv_sv.substr(12);
      else if (fs::is_directory(argv_sv))
        args.paths.push_back(argv_sv);
      else
        std::cerr << "Error: " << argv_sv << " is not a directory.\n";
    }
    return args;
  }
} // namespace arguments
