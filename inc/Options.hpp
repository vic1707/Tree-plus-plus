#pragma once
/* std */
#include <map>
#include <string_view>
#include <unordered_set>

namespace model {
  struct Options {
    /* Members */
    std::unordered_set<std::string_view> paths;
    std::unordered_set<std::string_view> sorters;
    std::map<std::string_view, std::unordered_set<std::string_view>> filters;
    std::string_view formatter;
    std::string_view indenter;
    size_t columns;
    size_t tab_size;
    // size_t nb_threads;
    bool redirect;

    /* Constructors */
    Options();
    Options(int argc, char** argv) : Options() {
      parse_args(argc, argv);
    }
    /* Methods */
    void parse_args(int argc, char** argv);
  };
} // namespace model
