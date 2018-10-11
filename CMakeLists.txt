cmake_minimum_required(VERSION 3.2)
project(pyiforest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#if (UNIX)
#add_definitions(-DSERIALIZATION=true)
#endif (UNIX)
#if (WIN32)
#endif(WIN32)
add_subdirectory(src)
include_directories(src)
set(SOURCE_FILES src/main.cpp)
#find_package(Armadillo REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/lib/eigen")

#include_directories(${ARMADILLO_INCLUDE_DIRS})
enable_testing()
add_subdirectory(test/lib/googletest)
add_subdirectory(test/unittest)
#add_subdirectory(test)
#add_subdirectory(python)

# look for Eigen
set(EIGEN3_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/lib/eigen)  ## Added by TZ
# look for Eigen
if (DEFINED ENV{EIGEN3_INCLUDE_DIR} AND NOT DEFINED EIGEN3_INCLUDE_DIR) # use env variable if not set
    set(EIGEN3_INCLUDE_DIR $ENV{EIGEN3_INCLUDE_DIR})
endif()
if (NOT Eigen_FOUND)
    include(${PROJECT_SOURCE_DIR}/src/lib/eigen/CTestConfig.cmake)
    set(Eigen_INCLUDE_DIR ${EIGEN3_INCLUDE_DIR})
endif()
include_directories("${EIGEN3_INCLUDE_DIR}")
#include_directories(${PROJECT_SOURCE_DIR}/lib)


add_executable(iforest ${SOURCE_FILES})
target_link_libraries(iforest iforestlib ${Eigen_INCLUDE_DIR}) #${ARMADILLO_LIBRARIES})

#add_subdirectory(pybind11)
#pybind11_add_module(pyiforest pybindwrapper.src)
