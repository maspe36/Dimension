cmake_minimum_required(VERSION 3.12)
project(DimensionServer VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(test)
