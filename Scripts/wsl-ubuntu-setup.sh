#!/bin/sh
set -e

sudo apt -y install cmake build-essential gcovr clang-format-22
sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-22 100
