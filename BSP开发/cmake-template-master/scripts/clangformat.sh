#!/usr/bin/env bash

# @Author: Farmer Li, 公众号: 很酷的程序员/RealCoolEngineer
# @Date: 2021-09-25

set -euf -o pipefail

usage(){
  echo "Usage: ${0} <src-dir> [-c/--check] [-h/--help]
    -c/--check
        Check the format but not perform actions
    -h/--help
        Show this page
    "
}

POSITIONAL=()
CHECK_ONLY=false
OPTIONS=(-style=file --verbose --sort-includes -i)

while [[ $# -gt 0 ]]
do
  key="$1"
  case $key in
    -c|--check)
      CHECK_ONLY=true
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      POSITIONAL+=("$1")
    ;;
  esac
  shift
done

if [[ ${#POSITIONAL[*]} -gt 0 ]]; then
  set -- "${POSITIONAL[*]}"
  FORMAT_DIR=$1
else
  usage
  exit 1
fi

if [[ ${CHECK_ONLY} == true ]]; then
  OPTIONS+=(-n -Werror)
  echo "Checking dir: ${1}"
else
  echo "Formating dir: ${1}"
fi

find "${FORMAT_DIR}" -type f \( -name '*.h' -or -name '*.hpp' -or -name '*.cpp' -or -name '*.c' -or -name '*.cc' \) -print | xargs clang-format ${OPTIONS[*]}
