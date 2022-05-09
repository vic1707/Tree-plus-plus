#!/bin/bash

# -h | --help: displays help
# -a | --all-files: displays hidden files and directories
# --dir-first: displays directories first
# -f | --foldable: IDE will be able to fold folders
# -r | --redirect: redirect output to <dirname>.tree
# every other argument is a path to a directory

## variables ##
hidden_files=("!" "-path" '*/.*') # hide hidden files and directories
foldable_prefix="│"
PATHS=()
type=("f" "d")
## variables ##

## arguments ##
while [[ $# -gt 0 ]]; do
  key="$1"
  case $key in
  -h | --help)
    echo "Usage: tree.sh [-h|--help] [-a|--all-files] [-f|--foldable] [-r|--redirect] [--children-count] [path]"
    exit 0
    ;;
  -a | --all-files)
    hidden_files=() # show hidden files and directories
    shift           # pass argument
    ;;
  -r | --redirect)
    redirect_to_file=1
    shift # pass argument
    ;;
  -f | --foldable)
    foldable_prefix=""
    shift # pass argument
    ;;
  --dir-first)
    type=("d" "f")
    shift # pass argument
    ;;
  *)
    [ -d "$key" ] &&
      PATHS+=("$(cd "$key" && pwd)") ||
      echo "error: $key is not a directory"
    shift # pass argument
    ;;
  esac
done

# if PATHS is empty we take current directory
if [ ${#PATHS[@]} -eq 0 ]; then
  PATHS+=("$PWD")
fi
## arguments ##

## fonctions ##
pad()   { printf "%s%$(($1 - ${#2}))s" "$2" ''; }
pad_r() { printf "%$(($1 - ${#2}))s%s" '' "$2"; }

tree_dir() {
  dir_count=$(($dir_count + 1))
  local directory=$1
  local prefix=${2:-""}

  # local children=("$directory"/*) # files and directories not separated

  local children
  IFS=$'\n' read -r -d '' -a children < <(
    for type in "${type[@]}"; do
      find "$directory" -mindepth 1 -maxdepth 1 -type $type "${hidden_files[@]}" | sort -V
    done
  )
  local child_count=${#children[@]}

  for idx in "${!children[@]}"; do
    local child=${children[$idx]}

    local child_prefix="$foldable_prefix   "
    local pointer="├── "

    if [ $idx -eq $((child_count - 1)) ]; then
      pointer="└── "
      child_prefix="    "
    fi

    pad 80 "${prefix}${pointer}${child##*/}"
    if [ -d "${child}" ]; then
      local size=$(du -sh "${child}" | cut -f 1)
      [ "$size" != "0B" ] && pad_r 40 "$size"
      printf "\n"
      tree_dir "$child" "${prefix}$child_prefix"
    else
      pad_r 40 "$(ls -lh "$child" | awk '{ printf("%8s - %2s %s %5s",$5,$6,$7,$8) }')"
      printf "\n"
      file_count=$((file_count + 1))
    fi
  done
}

handle_dir() {
  local dir_count=0
  local file_count=0
  local directory=$1

  printf "${directory##*/}\n"
  tree_dir "$directory"
  echo
  echo "$(($dir_count - 1)) directories, $file_count files - size: $(du -sh "${directory}" | cut -f 1)"
  echo
}
## fonctions ##

shopt -s nullglob
for path in "${PATHS[@]}"; do
  [ $redirect_to_file ] &&
    handle_dir "$path" >"${path##*/}.tree" ||
    handle_dir "$path"
done
shopt -u nullglob
