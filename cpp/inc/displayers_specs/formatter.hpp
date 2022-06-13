#pragma once
/* std */
#include <iostream>
#include <ostream>
#include <string_view>
/* custom */
#include <FileDirInfos.hpp>

namespace Formatter {
  class AFormatter {
    protected:
      /* Members */
      std::ostreambuf_iterator<char> stream = nullptr;
      size_t width;
    public:
      /* Constructors */
      AFormatter(size_t w) noexcept : width(w) {};
      virtual ~AFormatter() = default;

      /* Methods */
      void set_stream(std::ostream *s) {
        if (s == nullptr) throw std::invalid_argument("stream is nullptr");
        this->stream = std::ostreambuf_iterator<char>(*s);
      }
      virtual void display_file(const FileDirInfos::FileInfos *item, std::string_view prefix) = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item, std::string_view prefix) = 0;
  };
} // namespace Formatter
