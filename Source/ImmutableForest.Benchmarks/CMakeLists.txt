set(TARGET "ImmutableForest.Benchmarks")

add_executable("${TARGET}")

target_link_libraries("${TARGET}" PRIVATE benchmark::benchmark_main ImmutableForest)

target_include_directories("${TARGET}" INTERFACE "${CMAKE_CURRENT_LIST_DIR}")

file(GLOB_RECURSE "SOURCES" CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})
target_sources("${TARGET}" PRIVATE "${SOURCES}")

add_test(NAME "${TARGET}" COMMAND "${TARGET}" "--benchmark_out=${REPORTS_DIRECTORY}/${TARGET}.json" "--benchmark_out_format=json")
set_tests_properties("${TARGET}" PROPERTIES LABELS "Benchmark")
