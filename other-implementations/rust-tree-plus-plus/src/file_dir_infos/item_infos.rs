use core::fmt::{Display, Formatter, Result as FmtResult};
use std::fs;

use chrono::{DateTime, Local};
use size::Size;

/// A struct that contains the information of a file or a directory.
pub struct ItemInfos {
  /// The path of the file or directory.
  path: String,
  /// The last modification date of the file or directory.
  last_modified: DateTime<Local>,
  /// The name of the file or directory.
  name: String,
  /// The size of the file or directory.
  size: Size,
}

impl ItemInfos {
  /// Creates a new `ItemInfos` struct.
  pub fn new(path: &str) -> Self {
    let p = std::fs::canonicalize(path).unwrap_or_else(|_| std::path::PathBuf::from(path));

    let metadata = fs::metadata(&p).unwrap();

    Self {
      path: p.to_string_lossy().to_string(),
      last_modified: metadata.modified().map(|t| t.into()).unwrap(),
      name: p.file_name().map(|n| n.to_string_lossy().to_string()).unwrap(),
      size: Size::from_bytes(if p.is_dir() { 0 } else { metadata.len() }),
    }
  }

  pub fn add_size(&mut self, size: Size) {
    self.size = Size::from_bytes(self.size.bytes() + size.bytes());
  }
}

/// Implements the `Display` trait for `ItemInfos`.
impl Display for ItemInfos {
  fn fmt(&self, f: &mut Formatter<'_>) -> FmtResult {
    write!(f, "{} - {} ({} B)", self.name, self.size, self.size.bytes())
  }
}
