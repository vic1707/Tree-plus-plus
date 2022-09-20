use clap::Parser;

/// Rust implementation of the tree-plus-plus command line tool.
#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
pub struct Args {
    /// Boolean flag to enable listing hidden files
    #[clap(short, long)]
    pub all_files: bool,

    /// Boolean flag to show size in bytes
    #[clap(long)]
    pub size_in_bytes: bool,

    /// Boolean flag to redirect to external file
    #[clap(short, long)]
    pub redirect: bool,

    /// Size of tab indentation
    #[clap(long, default_value = "2")]
    pub tab_size: usize,

    /// List of sorting options
    #[clap(long)]
    pub sort_by: Vec<String>,

    /// Formatter to use
    #[clap(long, default_value = "name_only")]
    pub format: String,

    /// Indenter to use
    #[clap(long, default_value = "fancy")]
    pub indenter: String,

    /// Positional argument for the paths to list
    #[clap(parse(from_os_str), default_value = ".")]
    pub paths: Vec<std::path::PathBuf>,
}
