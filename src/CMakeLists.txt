project(pyiforest)
add_definitions(-std=c++11)
set(HEADER_FILES tree.hpp forest.hpp isolation_forest.hpp utility.hpp main.hpp facade_forest.hpp
        r_matrix.hpp stat/io_parser.hpp globals.hpp feature_contribution.hpp bagged_forest.hpp
         metric.hpp command_parser.hpp log_writer.hpp)
set(SOURCE_FILES tree.cpp forest.cpp isolation_forest.cpp utility.cpp facade_forest.cpp metric.cpp main.cpp
        stat/io_parser.cpp  log_writer.cpp
         command_parser.cpp bagged_forest.cpp)
#add_subdirectory(Eigen)
include_directories(lib)
add_library(iforestlib STATIC ${SOURCE_FILES} ${HEADER_FILES})
