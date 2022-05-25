#include "args.hpp"

namespace CLI {
  Arguments parse_args(int argc, char **argv) noexcept {
    Arguments args = Arguments{
      .opt = Options{false, false, false, false, false},
      .paths = {}
    };

    for (int i = 1; i < argc; i++) {
      auto argv_sv = std::string_view(argv[i]);
      if (argv_sv == "-h" || argv_sv == "--help") {
        std::cout << "Usage: ./tree [-h|--help] [-a|--all-files] [-f|--foldable] [-r|--redirect] [--dirs-first|--files-first] [path(s)]\n";
        exit(0);
      }
      else if (argv_sv == "-a" || argv_sv == "--all-files")
        args.opt.all_files = true;
      else if (argv_sv == "--dirs-first")
        args.opt.dirs_first = true;
      else if (argv_sv == "--files-first")
        args.opt.files_first = true;
      else if (argv_sv == "-f" || argv_sv == "--foldable")
        args.opt.foldable = true;
      else if (argv_sv == "-r" || argv_sv == "--redirect")
        args.opt.redirect = true;
      else if (fs::is_directory(argv_sv))
        args.paths.push_back(argv_sv);
      else
        std::cerr << "Error: " << argv_sv << " is not a directory.\n";
    }
    return args;
  }
} // namespace arguments
