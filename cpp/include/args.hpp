#ifndef ARGS_HPP
  #define ARGS_HPP
  /* std */
  #include <filesystem>
  #include <iostream>
  #include <string_view>
  #include <vector>

  namespace fs = std::filesystem;

  namespace arguments {
    struct options {
      bool all_files;
      bool dirs_first;
      bool files_first;
      bool foldable;
      bool redirect;
      // int nb_threads;
      // int size_indent;
      // bool size_in_bytes;
    };

    struct Arguments {
      options opt;
      std::vector<std::string_view> paths;
    };

    Arguments parse_args(int argc, char **argv) noexcept;
  } // namespace arguments
#endif // ARGS_HPP
