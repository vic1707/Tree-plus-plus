#include "args.hpp"

namespace arguments {
  args parse_args(int argc, char** argv) {
    args args = { {false, false, false, false, false}, {} };

    for (int i = 1; i < argc; i++) {
      auto argv_sv = std::string_view(argv[i]);
      if (argv_sv == "-h" || argv_sv == "--help") {
        std::cout << "Usage: ./tree [-h|--help] [-a|--all-files] [-f|--foldable] [-r|--redirect] [--dirs-first|--files-first] [path(s)]\n";
        exit(0);
      } else if (argv_sv == "-a" || argv_sv == "--all-files") {
        args.options.all_files = true;
      } else if (argv_sv == "--dirs-first") {
        args.options.dirs_first = true;
      } else if (argv_sv == "--files-first") {
        args.options.files_first = true;
      } else if (argv_sv == "-f" || argv_sv == "--foldable") {
        args.options.foldable = true;
      } else if (argv_sv == "-r" || argv_sv == "--redirect") {
        args.options.redirect = true;
      } else if (std::filesystem::is_directory(argv_sv)) {
        args.paths.push_back(argv_sv);
      } else {
        std::cerr << "Error: " << argv_sv << " is not a directory.\n";
      }
    }
    return args;
  }
}
