project(net CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SOURCES "*.h")

add_library(net ${SOURCES})
target_include_directories(net INTERFACE .)
set_target_properties(net PROPERTIES LINKER_LANGUAGE CXX)

