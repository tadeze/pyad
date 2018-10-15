include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runIforestTests
        common_util.hpp common_util.cpp )
#test_Forest.src
find_package(Eigen3)
target_link_libraries(runIforestTests gtest gtest_main)
target_link_libraries(runIforestTests iforestlib Eigen3::Eigen)
#test_Forest.src test_FacadeForest.src

