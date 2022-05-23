#include "main.hpp"

int main(int argc, char **argv) {
  auto args = arguments::parse_args(argc, argv);

  if (args.paths.empty())
    args.paths.push_back(".");

  for (auto path : args.paths) {
    Tree tree(path);
    Displayer::get_indenter("fancy", 4).display(tree.get_root());
  }
}
