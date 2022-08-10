#pragma once
/* lib */
#include "lib_thread_pool.hpp"

class ThreadPool {
  private:
    /* Members */
    static BS::thread_pool instance;
    static bool created;
    /* Constructors */
    ThreadPool() = delete;
    ThreadPool(const ThreadPool &) = delete;
    /* Operators */
    ThreadPool &operator=(const ThreadPool &) = delete;

  public:
    /* Methods */
    static BS::thread_pool *get_instance(unsigned int threads = 0) {
      if (!created) {
        if (threads > std::thread::hardware_concurrency())
          threads = std::thread::hardware_concurrency() - 1;
        instance.reset(threads);
      }
      return &instance;
    };
};
