project(DimensionServer_thirdparty)

message(\nRunning thirdparty CMakeLists.txt)
message(--------------------)

include(DownloadProject.cmake)
download_project(
        PROJ                catch2
        GIT_REPOSITORY      https://github.com/catchorg/Catch2
        GIT_TAG             v2.4.1
        SOURCE_DIR          ${CMAKE_SOURCE_DIR}/thirdparty/catch2
)

download_project(
        PROJ                json
        GIT_REPOSITORY      https://github.com/nlohmann/json
        GIT_TAG             v3.3.0
        SOURCE_DIR          ${CMAKE_SOURCE_DIR}/thirdparty/json
)


download_project(
        PROJ                pybind11
        GIT_REPOSITORY      https://github.com/pybind/pybind11
        GIT_TAG             v2.2.4
        SOURCE_DIR          ${CMAKE_SOURCE_DIR}/thirdparty/pybind11
)

add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include/catch2)

add_library(json INTERFACE)
target_include_directories(json INTERFACE ${json_SOURCE_DIR}/single_include/nlohmann)

add_library(pybind11 INTERFACE)
target_include_directories(pybind11 INTERFACE ${pybind11_SOURCE_DIR}/include)
