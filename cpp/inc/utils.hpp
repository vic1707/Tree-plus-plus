#ifndef UTILS_HPP
  #define UTILS_HPP
  /* std */
  #include <chrono>

  namespace Utils {
    template <typename TP>
    time_t to_time_t(TP tp) {
      auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp - TP::clock::now()
        + std::chrono::system_clock::now());
      return std::chrono::system_clock::to_time_t(sctp);
    };
  } // namespace Utils

#endif // UTILS_HPP
