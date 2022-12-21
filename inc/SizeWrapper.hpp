#pragma once
/* FMT */
#include <fmt/format.h>
#include <fmt/ostream.h>
/* SIZE */
#include <size/size.hpp>
#include <size/size_fmt.hpp>
/* STD */
#include <iomanip>

struct SizeWrapper: public size::Size<size::Base::Base2> {
  static bool size_in_bytes;
  /* Constructors */
  using size::Size<size::Base::Base2>::Size;
  /* Operators */
  friend inline std::ostream& operator<<(std::ostream& os, const SizeWrapper& s) {
    if (size_in_bytes)
      os << fmt::format("({} B) - {: >11.2#%f %U}", s.bytes(), static_cast<const size::Size<size::Base::Base2>&>(s));
    else
      os << static_cast<const size::Size<size::Base::Base2>&>(s);
    return os;
  }
};

template <> struct fmt::formatter<SizeWrapper> : ostream_formatter {};
