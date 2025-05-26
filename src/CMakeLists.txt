
# cmake-lint: disable=C0103
set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")
# cmake-lint: disable=C0103
set(JSON_MultipleHeaders
    OFF
    CACHE INTERNAL "")
# add nlohmann::json library
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/json" "extern/json" EXCLUDE_FROM_ALL)

include(FetchContent)
# antlr
# 🔹 Fetch the ANTLR4 C++ runtime from GitHub
FetchContent_Declare(
  antlr4_runtime
  GIT_REPOSITORY https://github.com/antlr/antlr4.git
  GIT_TAG        4.13.1
)

# Build only the C++ runtime, skip the Java tools
set(ANTLR4_BUILD_SHARED OFF CACHE BOOL "" FORCE) # no shared (dynamic) library version (.so/.dll)
set(ANTLR4_BUILD_STATIC ON CACHE BOOL "" FORCE) # static library (.a)
set(ANTLR4_BUILD_TOOLS OFF CACHE BOOL "" FORCE) # Don’t build the `antlr4` Java CLI tool

FetchContent_MakeAvailable(antlr4_runtime)

# main project library
add_library(
  ${PROJECT_NAME} SHARED
  ${PROJECT_SOURCE_DIR}/include/Definition.hpp
  ${PROJECT_SOURCE_DIR}/include/GateType.hpp
  ${PROJECT_SOURCE_DIR}/include/QGate.hpp
  ${PROJECT_SOURCE_DIR}/include/QCircuit.hpp
  ${PROJECT_SOURCE_DIR}/include/decompose/Clifford_T.hpp
  QCircuit.cpp
  QGate.cpp
  decompose/Clifford_T.cpp
  parsers/ParseQASM.cpp
  parsers/ParseQASM3.cpp
  parsers/antlr-generated-parser/qasm3Parser.cpp
  parsers/antlr-generated-parser/qasm3Lexer.cpp
  parsers/antlr-generated-parser/qasm3ParserBaseListener.cpp
  parsers/antlr-generated-parser/qasm3ParserListener.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
message(STATUS "ANTLR4 runtime source dir: ${antlr4_runtime_SOURCE_DIR}")

# set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                                  ${PROJECT_BINARY_DIR}/include
                                                  ${antlr4_runtime_SOURCE_DIR}/runtime/Cpp/runtime/src
                                                  ${PROJECT_SOURCE_DIR}/src/parsers/antlr-generated-parser
)

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)