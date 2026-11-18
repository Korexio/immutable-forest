#!/bin/sh
set -u

cd "$(dirname "$0")/../Source" || exit 1

cmake --workflow --preset linux-x86-64-release
exit_code=$?

printf "Press Enter to continue . . . "
read -r _ || true
exit "$exit_code"
