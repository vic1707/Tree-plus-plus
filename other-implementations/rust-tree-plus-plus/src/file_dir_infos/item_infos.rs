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
    let p = std::fs::canonicalize(path).unwrap();
    let last_modified = chrono::DateTime::<chrono::Local>::from(std::fs::metadata(&p).unwrap().modified().unwrap());
    let size = Size::from_bytes(std::fs::metadata(&path).unwrap().len());
    return Self {
      path: p.as_os_str().to_str().unwrap().to_string(),
      last_modified,
      name: p
      .file_name()
      .unwrap()
      .to_str()
      .unwrap()
      .to_string(),
      size,
    };
  }
}
