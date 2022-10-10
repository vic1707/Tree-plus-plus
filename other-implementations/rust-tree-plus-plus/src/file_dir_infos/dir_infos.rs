use crate::file_dir_infos::file_infos::FileInfos;
use crate::file_dir_infos::item_infos::ItemInfos;
use crate::file_dir_infos::items_count::ChildCount;

use core::fmt::{Display, Formatter, Result as FmtResult};

/// An enum that represents a directory or a file.
enum Children {
  File(FileInfos),
  Dir(DirInfos),
}

/// A struct that contains the information of a directory.
pub struct DirInfos {
  infos: ItemInfos,
  children: Vec<Children>,
  count: ChildCount,
}

impl DirInfos {
  /// Creates a new `DirInfos` struct.
  pub fn new(path: &str) -> Self {
    let mut count = ChildCount::new();
    let children = std::fs::read_dir(&path)
      .unwrap()
      .map(|f| {
        let p = f.unwrap().path();
        if p.is_dir() {
          count.add_dir(&DirInfos::new(path).count);
          Children::Dir(DirInfos::new(path))
        } else {
          count.add_file();
          Children::File(FileInfos::new(path))
        }
      })
      .collect();
    Self {
      infos: ItemInfos::new(path),
      count,
      children,
    }
  }
}

/// Implements the `Display` trait for `DirInfos`.
impl Display for DirInfos {
  fn fmt(&self, f: &mut Formatter<'_>) -> FmtResult {
    write!(f, "TODO")
  }
}
