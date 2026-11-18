# Immutable Forest

A C++20 header-only template library for immutable trees.

## Features

- Fast, lock-free concurrent reads.
- Heterogeneous key comparison to avoid allocations/conversions.
- Forwarding references to avoid unnecessary copies.
- Binary search + std::vector to keep memory/CPU overhead minimal.
- Nodes are linked via shared pointers - allowing re-use and low-cost snapshots.

## Build

Presets are named `<os>-<architecture>-<configuration>`:

- `windows-x86-64-debug`
- `windows-x86-64-release`
- `linux-x86-64-debug`
- `linux-x86-64-release`

Configure, build and test:

```sh
cd Source
cmake --preset windows-x86-64-debug
cmake --build --preset windows-x86-64-debug
ctest --preset windows-x86-64-debug-tests
```

Or run all steps at once via the workflow preset:

```sh
cd Source
cmake --workflow --preset windows-x86-64-debug
```

Alternatively, run the script of the same name in [`Scripts`](Scripts/), e.g. [`windows-x86-64-debug.bat`](Scripts/windows-x86-64-debug.bat) or [`linux-x86-64-debug.sh`](Scripts/linux-x86-64-debug.sh).

## Repository structure

| Path                                                                      | Description               |
|---------------------------------------------------------------------------|---------------------------|
| [Artifacts](./Artifacts/)                                                 | Build artifacts.          |
| [Scripts](./Scripts/)                                                     | Scripts.                  |
| [Source/ImmutableForest](./Source/ImmutableForest/)                       | Main library.             |
| [Source/ImmutableForest.Tests](./Source/ImmutableForest.Tests/)           | Google test project.      |
| [Source/ImmutableForest.Benchmarks](./Source/ImmutableForest.Benchmarks/) | Google benchmarks project.|

## Tech stack

* [Git](https://git-scm.com/)
* [CMake](https://cmake.org/)
* [Google Test](https://google.github.io/googletest/)
* [Google Benchmark](https://github.com/google/benchmark)
* [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
* [EditorConfig](https://editorconfig.org/)
* [Visual Studio Code](https://code.visualstudio.com/)
* [Visual Studio](https://visualstudio.microsoft.com/)
