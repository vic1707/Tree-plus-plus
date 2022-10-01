use core::fmt::{Display, Formatter, Result as FmtResult};

struct ItemsCount {
  files: usize,
  dirs: usize,
}

impl ItemsCount {
  const fn new() -> Self {
    return Self { files: 0, dirs: 0 };
  }

  fn add_file(&mut self) {
    self.files += 1;
  }

  fn rm_file(&mut self) {
    self.files -= 1;
  }

  fn add_dir(&mut self, other: &Self) {
    self.files += other.files;
    self.dirs += other.dirs + 1;
  }

  fn rm_dir(&mut self, other: &Self) {
    self.files -= other.files;
    self.dirs -= other.dirs + 1;
  }
}

pub struct ChildCount {
  local: ItemsCount,
  total: ItemsCount,
}

impl ChildCount {
  pub fn new() -> Self {
    return Self {
      local: ItemsCount::new(),
      total: ItemsCount::new(),
    };
  }

  pub fn add_file(&mut self) {
    self.local.add_file();
    self.total.add_file();
  }

  pub fn rm_file(&mut self) {
    self.local.rm_file();
    self.total.rm_file();
  }

  pub fn add_dir(&mut self, other: &Self) {
    self.local.add_dir(&other.local);
    self.total.add_dir(&other.total);
  }

  pub fn rm_dir(&mut self, other: &Self) {
    self.local.rm_dir(&other.local);
    self.total.rm_dir(&other.total);
  }
}

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
    return write!(
      f,
      "{} director{}{} and {} file{}{}",
      self.local.dirs, dirs_plural, total_dirs, self.local.files, files_plural, total_files
    );
  }
}
