cmake_minimum_required(VERSION 3.15)

project(
    qcore 
    VERSION 1.0
    LANGUAGES CXX
    DESCRIPTION "QCORE: A library for core quantum gate and circuit representation")

# check whether the submodule ``modulename`` is correctly cloned in the ``/extern`` directory.
macro(CHECK_SUBMODULE_PRESENT modulename)
  if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/${modulename}/CMakeLists.txt")
    message(
      FATAL_ERROR
        "${modulename} submodule not cloned properly. \
        Please run `git submodule update --init --recursive` \
        from the main project directory")
  endif()
endmacro()

check_submodule_present(json)

# add main library code
add_subdirectory(src)

# add Python binding code
option(BINDINGS "Configure for building Python bindings" OFF)
if(BINDINGS)
    check_submodule_present(pybind11)
    check_submodule_present(pybind11_json)
    add_subdirectory(qcore)
endif()

# add tests
# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        parser_test
        test/qasm3_parser_test.cpp
)
target_link_libraries(
        parser_test
        PRIVATE
        GTest::gtest_main
        ${PROJECT_NAME}
)

target_compile_definitions(parser_test PRIVATE
        TEST_RESOURCES_DIR="${CMAKE_SOURCE_DIR}/test/test_resources"
)

include(GoogleTest)
gtest_discover_tests(parser_test)
