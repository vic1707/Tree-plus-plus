#include "displayer.hpp"
#include "displayers/classic.hpp"

// const std::array<std::string_view, 2> entry_pointers = { "├── ", "└── " };
// const std::array<std::string_view, 2> continuity_pointers = { "│   ", "    " };

Displayer *Displayer::get_Displayer() {
  return new Classic;
}

Displayer *Displayer::get_Displayer(auto ...args) {
  return new Classic(args...);
}
