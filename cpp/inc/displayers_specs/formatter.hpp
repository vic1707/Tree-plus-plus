#pragma once
/* std */
#include <ostream>
#include <string_view>
/* custom */
#include <FileDirInfos.hpp>

namespace Formatter {
  class AFormatter {
    protected:
      /* Members */
      std::ostream* stream = nullptr;
      size_t width;
    public:
      /* Constructors */
      AFormatter(size_t w) noexcept : width(w) {};
      virtual ~AFormatter() = default;
      void set_stream(std::ostream* s) {
        if (s == nullptr) throw std::invalid_argument("stream is nullptr");
        this->stream = s;
      }

      /* Methods */
      virtual void display_file(const FileDirInfos::FileInfos *item, std::string_view prefix) noexcept = 0;
      virtual void display_folder(const FileDirInfos::DirInfos *item, std::string_view prefix) noexcept = 0;
  };
} // namespace Formatter
