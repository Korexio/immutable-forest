find_program("CLANG_FORMAT" "clang-format"
    HINTS "C:/Program Files/Microsoft Visual Studio/18/Professional/VC/Tools/Llvm/x64/bin"
    REQUIRED)
message(STATUS "Using '${CLANG_FORMAT}'.")

file(GLOB_RECURSE "CLANG_FORMAT_FILES" CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
set(CMAKE_FOLDER "Third-Party/clang-format")
add_custom_target("clang-format"
    COMMAND "${CLANG_FORMAT}" "-i" ${CLANG_FORMAT_FILES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
unset(CMAKE_FOLDER)
