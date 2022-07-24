project(simple_client CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES 
    simple_client.cpp
)

add_executable(simple_client ${SOURCES})
target_link_libraries(simple_client PUBLIC net)
