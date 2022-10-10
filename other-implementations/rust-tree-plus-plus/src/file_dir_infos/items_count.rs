use core::fmt::{Display, Formatter, Result as FmtResult};

/// A struct that represents the number of items in a directory.
struct ItemsCount {
  /// The number of files in the directory.
  files: usize,
  /// The number of directories in the directory.
  dirs: usize,
}

impl ItemsCount {
  /// Creates a new `ItemsCount` struct.
  const fn new() -> Self {
    Self { files: 0, dirs: 0 }
  }

  /// Increments the number of files in the directory.
  fn add_file(&mut self) {
    self.files += 1;
  }

  /// Decrements the number of files in the directory.
  fn rm_file(&mut self) {
    self.files -= 1;
  }

  /// Increments the number of items in the directory using the numbers
  /// from another `ItemsCount` struct.
  fn add_dir(&mut self, other: &Self) {
    self.files += other.files;
    self.dirs += other.dirs + 1;
  }

  /// Decrements the number of items in the directory using the numbers
  /// from another `ItemsCount` struct.
  fn rm_dir(&mut self, other: &Self) {
    self.files -= other.files;
    self.dirs -= other.dirs + 1;
  }
}

/// A struct that represents the local number of items in a directory as well
/// as the global number of items in the directory.
pub struct ChildCount {
  local: ItemsCount,
  total: ItemsCount,
}

impl ChildCount {
  /// Creates a new `ChildCount` struct.
  pub fn new() -> Self {
    Self {
      local: ItemsCount::new(),
      total: ItemsCount::new(),
    }
  }

  /// Increments the number of files in the directory.
  pub fn add_file(&mut self) {
    self.local.add_file();
    self.total.add_file();
  }

  /// Decrements the number of files in the directory.
  pub fn rm_file(&mut self) {
    self.local.rm_file();
    self.total.rm_file();
  }

  /// Increments the number of items in the directory using the numbers
  /// from another `ChildCount` struct.
  pub fn add_dir(&mut self, other: &Self) {
    self.local.dirs += 1;
    self.total.add_dir(&other.total);
  }

  /// Decrements the number of items in the directory using the numbers
  /// from another `ChildCount` struct.
  pub fn rm_dir(&mut self, other: &Self) {
    self.total.rm_dir(&other.total);
  }
}

/// Implements the `Display` trait for the `ChildCount` struct.
impl Display for ChildCount {
  fn fmt(&self, f: &mut Formatter<'_>) -> FmtResult {
    if self.total.dirs == 0 && self.total.files == 0 {
      return write!(f, "Empty directory");
    }

    let dirs_plural = if self.local.dirs > 1 { "ies" } else { "y" };
    let files_plural = if self.local.files > 1 { "s" } else { "" };
    let total_dirs = if self.local.dirs != self.total.dirs {
      format!(" ({} total)", self.total.dirs)
    } else {
      String::new()
    };
    let total_files = if self.local.files != self.total.files {
      format!(" ({} total)", self.total.files)
    } else {
      String::new()
    };
    write!(
      f,
      "{} director{}{} and {} file{}{}",
      self.local.dirs, dirs_plural, total_dirs, self.local.files, files_plural, total_files
    )
  }
}
