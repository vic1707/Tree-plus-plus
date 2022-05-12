#include "args.hpp"

arguments::args arguments::parse_args(int argc, char** argv) {
  arguments::args args = { {false, false, false, false}, {} };

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      std::cout << "Usage: ./tree [-h|--help] [-a|--all-files] [-f|--foldable] [-r|--redirect] [--children-count] [path(s)]\n";
      exit(0);
    } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all-files") == 0) {
      args.options.all_files = true;
    } else if (strcmp(argv[i], "--dir-first") == 0) {
      args.options.dir_first = true;
    } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--foldable") == 0) {
      args.options.foldable = true;
    } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--redirect") == 0) {
      args.options.redirect = true;
    } else {
      if (std::filesystem::directory_entry(argv[i]).is_directory())
        args.paths.push_back(argv[i]);
    }
  }
  return args;
}
