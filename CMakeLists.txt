cmake_minimum_required(VERSION 3.2)
project(pyiforest)

add_subdirectory(pybind11)
pybind11_add_module(pyiforest pybindwrapper.cpp)
