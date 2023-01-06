use crate::file_dir_infos::item_infos::ItemInfos;

use core::fmt::{Display, Formatter, Result as FmtResult};

/// A struct that contains the information of a file.
pub struct FileInfos {
  pub infos: ItemInfos,
}

impl FileInfos {
  /// Creates a new `FileInfos` struct.
  pub fn new(path: &str) -> Self {
    Self {
      infos: ItemInfos::new(path),
    }
  }
}

/// Implements the `Display` trait for `FileInfos`.
impl Display for FileInfos {
  fn fmt(&self, f: &mut Formatter<'_>) -> FmtResult {
    write!(f, "{}", self.infos)
  }
}
