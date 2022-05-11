#ifndef ARGS_HPP
  #define ARGS_HPP
  #include <algorithm>

  bool cmdOptionExists(char** begin, char** end, const char** &option);
  char* getCmdOption(char** begin, char** end, const char** &option);

#endif
