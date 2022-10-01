use clap::Parser;

/// Rust implementation of the tree-plus-plus command line tool.
#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
pub struct Args {
  /// Boolean flag to enable listing hidden files
  #[clap(short, long)]
  pub all_files: bool,

  /// Size of tab indentation
  #[clap(long, default_value = "2")]
  pub tab_size: usize,

  /// Positional argument for the paths to list
  #[clap(default_value = ".")]
  pub paths: Vec<String>,
}
