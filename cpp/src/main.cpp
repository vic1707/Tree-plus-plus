#include "main.hpp"

int get_terminal_width() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int main(int argc, char **argv) {
  auto args = CLI::parse_args(argc, argv);

  if (args.paths.empty())
    args.paths.push_back(".");

  for (auto path : args.paths) {
    Tree tree(path);
    Displayer::get_indenter("fancy", 4).display(tree.get_root());
  }
}
