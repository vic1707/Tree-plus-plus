use crate::file_dir_infos::item_infos::ItemInfos;

/// A struct that contains the information of a file.
pub struct FileInfos(ItemInfos);

impl FileInfos {
  /// Creates a new `FileInfos` struct.
  pub fn new(path: &str) -> Self {
    Self(ItemInfos::new(path))
  }
}
