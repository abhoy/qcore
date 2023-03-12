
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

# main project library
add_library(
  ${PROJECT_NAME} SHARED
  ${PROJECT_SOURCE_DIR}/include/definition.hpp
  ${PROJECT_SOURCE_DIR}/include/gatetype.hpp
  ${PROJECT_SOURCE_DIR}/include/qgate.hpp
  ${PROJECT_SOURCE_DIR}/include/qcircuit.hpp
  qcircuit.cpp
  qgate.cpp
  parsers/parseQASM.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                                  ${PROJECT_BINARY_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)