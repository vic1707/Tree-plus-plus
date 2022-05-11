#include "args.hpp"

bool cmdOptionExists(char** begin, char** end, const char** &option) {
  return std::find(begin, end, option) != end;
}

char* getCmdOption(char** begin, char** end, const char** &option) {
  char** itr = std::find(begin, end, option);
  if (itr != end && ++itr != end) return *itr;
  return 0;
}
