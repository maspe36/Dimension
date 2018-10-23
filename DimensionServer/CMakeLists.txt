cmake_minimum_required(VERSION 3.12)
project(DimensionServer VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty/catch)
add_subdirectory(thirdparty/jsoncpp)
add_subdirectory(thirdparty/pybind11)

add_subdirectory(src)
add_subdirectory(test)
