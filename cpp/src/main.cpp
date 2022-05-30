#include "main.hpp"

int main(int argc, char **argv) {
  auto args = CLI::parse_args(argc, argv);
  auto &displ = Displayer::get_indenter(args.displayer_options);
  SizeUnit::SizeUnit::size_in_bytes = args.opt.size_in_bytes;

  for (auto path : args.paths)
    displ.traverse(Tree(path, args.opt.hidden).get_root(), args.displayer_options.redirect);
}
