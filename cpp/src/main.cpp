#include "main.hpp"

int get_terminal_width() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  if (w.ws_col == 0) return 150;
  return w.ws_col;
}

int main(int argc, char **argv) {
  auto args = CLI::parse_args(argc, argv);
  args.displayer_options.columns = get_terminal_width();
  auto &displ = Displayer::get_indenter(args.displayer_options);

  for (auto path : args.paths)
    displ.traverse(Tree(path, args.opt.hidden).get_root(), args.displayer_options.redirect);
}
