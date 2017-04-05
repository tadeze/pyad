include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runIforestTests
        test_basiccheck.cpp test_metric.cpp common_util.hpp test_tree.cpp test_Forest.cpp test_FacadeForest.cpp common_util.cpp test_utility.cpp)
target_link_libraries(runIforestTests gtest gtest_main)
target_link_libraries(runIforestTests iforestlib)

