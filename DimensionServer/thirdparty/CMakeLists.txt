project(DimensionServer_thirdparty)

message("\nRunning thirdparty CMakeLists.txt")
message(--------------------)

message("Adding boost...")
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.58.0 REQUIRED system log)

message("Adding libpqxx...")
find_package(PostgreSQL 10 REQUIRED)
find_package(libpqxx REQUIRED)

message("Adding Catch2...")
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE Catch2/single_include/catch2)

message("Adding json...")
add_library(json INTERFACE)
target_include_directories(json INTERFACE json/single_include/nlohmann)

message("Adding pybind11...")
add_subdirectory(pybind11)

set(thirdparty_includes
        ${Boost_INCLUDE_DIRS}
        ${LIBPQXX_INCLUDE_DIRS}
        CACHE INTERNAL "")

set(thirdparty_libs
        ${Boost_LIBRARIES}
        ${LIBPQXX_LIBRARY_DIRS}
        Threads::Threads
        catch2
        json
        pybind11::embed
        CACHE INTERNAL "")
