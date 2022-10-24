#pragma once

namespace size {
  /// An enumeration of supported styles to be used when formatting/printing a [`Size`] type,
  /// specifying how the unit should be spelled out.
  enum class Style: int {
    /// Abbreviated style, e.g. "1024 KB" and "1.29 GiB"
    Abbreviated,
    /// Abbreviated, lowercase style, e.g. "1024 kb" and "1.29 gib"
    AbbreviatedLowercase,
    /// Full unit name style, e.g. "1024 Kilobytes" and "1.29 Gibibytes"
    Full,
    /// Full, lowercase unit name style, e.g. "1024 kilobytes" and "1.29 gibibytes"
    FullLowercase
  };

  constexpr const Style DEFAULT_STYLE = Style::Abbreviated;
}; // namespace size
