#pragma once

namespace size {
  /// An enumeration of supported bases to use for generating textual descriptions of sizes.
  /// [`Base::Base10`] is the "usual" units like "kilobyte" and "exabyte", while [`Base::Base2`] is
  /// the SI/memory units like "mebibyte" and "tebibyte", (more often referred to as "MiB" and "TiB",
  /// respectively).
  enum class Base: int {
    /// Base-2 units like "kibibyte" and "mebibyte", more often referred to via their abbreviations
    /// ("KiB" and "MiB", respectively). Each unit is 1024 times greater than the preceding one.
    Base2,
    /// Base-10 units like "kilobyte" and "megabyte", more often referred to via their abbreviations
    /// ("KB" and "MB", respectively). Each unit is 1000 times greater than the preceding one.
    Base10,
  };

  constexpr const Base DEFAULT_BASE = Base::Base2;
}; // namespace size
