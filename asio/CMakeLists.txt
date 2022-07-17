cmake_minimum_required(VERSION 3.0.0)
project(sandbox VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

SET(BOOST_ROOT "~/proj/sdk/asio-1.22.2/include") 
include_directories(${BOOST_ROOT})

# add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_CHRONO_HEADER_ONLY -DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_subdirectory(example)