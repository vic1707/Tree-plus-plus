mod file_dir_infos;
mod options;

use clap::Parser;

fn main() {
    let args = options::Args::parse();

    for path in args.paths.iter() {
        println!("{:?}", path);
    }
}
