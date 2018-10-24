project(DimensionServer_thirdparty)

message(\nRunning thirdparty CMakeLists.txt)
message(--------------------)

message("Adding Catch2...")
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE Catch2/single_include/catch2)

message("Adding json...")
add_library(json INTERFACE)
target_include_directories(json INTERFACE json/single_include/nlohmann)

message("Adding pybind11...")
add_library(pybind11 INTERFACE)
target_include_directories(pybind11 INTERFACE pybind11/include)
