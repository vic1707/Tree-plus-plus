#include "main.hpp"

int get_terminal_width() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int main(int argc, char **argv) {
  auto args = CLI::parse_args(argc, argv);
  args.displayer_options.columns = get_terminal_width();
  auto &displ = Displayer::get_indenter(args.displayer_options);

  for (auto path : args.paths) {

    if (args.displayer_options.redirect) freopen((fs::canonical(path).filename().string()+".tree").c_str(),"w",stdout); // redirect stdout to file <path>.tree
    Tree tree(path);
    displ.display(tree.get_root());
  }
}
