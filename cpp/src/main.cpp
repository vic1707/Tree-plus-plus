#include "main.hpp"

int main(int argc, char **argv) {
  auto args = arguments::parse_args(argc, argv);

  if (args.paths.empty())
    args.paths.push_back(".");

  for (auto path : args.paths) {
    Tree tree(path);
    auto displayer = Displayer::get_Displayer();
    displayer->display(tree.get_root());
  }
}
