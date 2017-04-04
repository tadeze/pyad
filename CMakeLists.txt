cmake_minimum_required(VERSION 3.6)
project(pyiforest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
add_executable(iforest ${SOURCE_FILES})

include_directories(cpp)
add_subdirectory(cpp)

add_subdirectory(test)
target_link_libraries(iforest iforestlib)
