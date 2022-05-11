#ifndef ARGS_HPP
  #define ARGS_HPP
  #include <algorithm>
  #include <iostream>
  #include <vector>

  namespace arguments {
    struct args
    {
      bool all_files;
      bool dir_first;
      bool foldable;
      bool redirect;
      std::vector<char*> paths;
    };

    args parse_args(int argc, char** argv);
  }

#endif
