#pragma once
/* std */
#include <filesystem>
#include <iostream>
// includes stoi
#include <string>
#include <string_view>
#include <vector>
/* custom */
#include "displayer.hpp"

namespace fs = std::filesystem;

namespace CLI {
  struct Options {
    bool redirect;
    // int nb_threads;
    // bool size_in_bytes;
  };

  struct Arguments {
    Options opt;
    Displayer::DisplayerOptions displayer_options;
    std::vector<std::string_view> paths;
  };

  Arguments parse_args(int argc, char **argv) noexcept;
} // namespace CLI
