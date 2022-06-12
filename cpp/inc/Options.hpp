#pragma once
#include <unordered_set>
#include <string_view>

namespace model {
  struct Options {
    /* Members */
    std::unordered_set<std::string_view> paths;
    std::unordered_set<std::string_view> sorters;
    std::string_view formatter;
    std::string_view indenter;
    size_t columns;
    size_t tab_size;
    // size_t nb_threads;
    bool redirect;
    bool hidden;
    bool size_in_bytes;

    /* Constructors */
    Options() noexcept;
    Options(int argc, char** argv) : Options() {
      parse_args(argc, argv);
    }
    /* Methods */
    void parse_args(int argc, char** argv);
  };
} // namespace model
