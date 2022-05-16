#include "main.hpp"

int main(int argc, char** argv) {
  arguments::args args = arguments::parse_args(argc, argv);

  if (args.paths.empty()) args.paths.push_back(".");
  for (auto path : args.paths) {
     Tree tree(path);
    Classic classic;
    classic.display(tree.get_root(), 0);
  }
}
