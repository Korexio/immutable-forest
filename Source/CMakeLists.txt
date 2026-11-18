cmake_minimum_required(VERSION 3.25)

project("ImmutableForest" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Third-Party/CMake")

include("FetchContent")

FetchContent_Declare("googletest"
    URL "https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz"
    URL_HASH "SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926"
    FIND_PACKAGE_ARGS NAMES "GTest"
)
set(CMAKE_FOLDER "Third-Party/GoogleTest")
FetchContent_MakeAvailable("googletest")

FetchContent_Declare("benchmark"
    URL "https://github.com/google/benchmark/archive/refs/tags/v1.9.1.tar.gz"
    URL_HASH "SHA256=32131c08ee31eeff2c8968d7e874f3cb648034377dfc32a4c377fa8796d84981"
    FIND_PACKAGE_ARGS NAMES "benchmark"
)
set(CMAKE_FOLDER "Third-Party/GoogleBenchmark")
FetchContent_MakeAvailable("benchmark")

unset(CMAKE_FOLDER)

add_compile_options(
    "$<$<CXX_COMPILER_ID:MSVC>:/Wall;/permissive-;/external:anglebrackets;/external:W0>"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4820;/wd4710;/wd4711>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic>"
)

include("${CMAKE_SOURCE_DIR}/CMake/clang-format.cmake")

if(NOT REPORTS_DIRECTORY)
    message(FATAL_ERROR "REPORTS_DIRECTORY is not set. Use a configure preset or pass -DREPORTS_DIRECTORY=<path>.")
endif()
file(MAKE_DIRECTORY "${REPORTS_DIRECTORY}")

enable_testing()

add_subdirectory("ImmutableForest")
add_subdirectory("ImmutableForest.Tests")
add_subdirectory("ImmutableForest.Benchmarks")

add_dependencies("ImmutableForest" "clang-format")
