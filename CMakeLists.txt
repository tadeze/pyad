cmake_minimum_required(VERSION 3.2)
project(pyiforest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(cpp)
include_directories(cpp)
set(SOURCE_FILES cpp/main.cpp)
add_subdirectory(test)

add_executable(pyiforest ${SOURCE_FILES})
target_link_libraries(pyiforest iforestlib)


#add_subdirectory(pybind11)
#pybind11_add_module(pyiforest pybindwrapper.cpp)
