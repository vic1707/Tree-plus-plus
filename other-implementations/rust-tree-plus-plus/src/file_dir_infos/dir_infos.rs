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
    let mut infos = ItemInfos::new(path);
    let children = std::fs::read_dir(&path)
      .unwrap()
      .map(|c| {
        let p = c.unwrap().path();
        let path = p.to_str().unwrap();
        if p.is_dir() {
          let dir = DirInfos::new(path);
          infos.add_size(dir.infos.size);
          count.add_dir(&dir.count);
          Children::Dir(dir)
        } else {
          let file = FileInfos::new(path);
          infos.add_size(file.infos.size);
          count.add_file();
          Children::File(file)
        }
      })
      .collect();
    Self { infos, count, children }
  }
}

/// Implements the `Display` trait for `DirInfos`.
impl Display for DirInfos {
  fn fmt(&self, f: &mut Formatter<'_>) -> FmtResult {
    write!(f, "{}", self.infos)
  }
}
