#ifndef ARGS_HPP
  #define ARGS_HPP
  #include <algorithm>
  #include <filesystem>
  #include <iostream>
  #include <string_view>
  #include <vector>

  namespace arguments {
    struct options {
      bool all_files;
      bool dirs_first;
      bool files_first;
      bool foldable;
      bool redirect;
    };

    using Options = options;
    struct args {
      Options options;
      std::vector<std::string_view> paths;
    };

    args parse_args(int argc, char** argv);
  }

#endif
