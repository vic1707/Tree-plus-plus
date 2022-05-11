#include "tree.hpp"
#include "args.hpp"

int main(int argc, char** argv) {
  arguments::args args = arguments::parse_args(argc, argv);

  if (args.paths.empty()) args.paths.push_back((char*)".");
  for (char* path : args.paths) Tree tree(path, args);
}
