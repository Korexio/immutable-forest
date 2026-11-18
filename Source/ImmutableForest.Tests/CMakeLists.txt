set(TARGET "ImmutableForest.Tests")

add_executable("${TARGET}")

target_link_libraries("${TARGET}"
    PRIVATE GTest::gtest_main ImmutableForest )

target_include_directories("${TARGET}"
    INTERFACE "${CMAKE_CURRENT_LIST_DIR}")

file(GLOB_RECURSE "SOURCES" CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})
target_sources("${TARGET}" PRIVATE "${SOURCES}")

include(GoogleTest)
gtest_discover_tests("${TARGET}" XML_OUTPUT_DIR "${REPORTS_DIRECTORY}/${TARGET}" PROPERTIES LABELS "Test" FIXTURES_REQUIRED "${TARGET}.Coverage")

option(ENABLE_COVERAGE "Generate a coverage report when running unit tests." OFF)
if(ENABLE_COVERAGE)
    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(FATAL_ERROR "ENABLE_COVERAGE requires GCC.")
    endif()
    find_program("GCOVR" "gcovr" REQUIRED)
    message(STATUS "Using '${GCOVR}'.")

    target_compile_options("${TARGET}" PRIVATE "--coverage")
    target_link_options("${TARGET}" PRIVATE "--coverage")

    set(COVERAGE_REPORT "${REPORTS_DIRECTORY}/${TARGET}.Coverage")
    file(MAKE_DIRECTORY "${COVERAGE_REPORT}")
    add_test(NAME "${TARGET}.Coverage"
        COMMAND "${GCOVR}"
            "--root" "${CMAKE_SOURCE_DIR}"
            "--filter" "${CMAKE_SOURCE_DIR}/ImmutableForest/"
            "--delete"
            "--print-summary"
            "--cobertura" "${COVERAGE_REPORT}.xml"
            "--html-details" "${COVERAGE_REPORT}/index.html"
            "--html-theme" "github.dark-green"
            "${CMAKE_BINARY_DIR}")
    set_tests_properties("${TARGET}.Coverage" PROPERTIES
        FIXTURES_CLEANUP "${TARGET}.Coverage"
        LABELS "Coverage")
endif()
