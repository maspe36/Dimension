project(DimensionServer_test)

message("\nRunning test CMakeLists.txt")
message(--------------------)

set(test_files
        CatchMain.cpp
        Python/test_Interpreter.cpp)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.58.0 REQUIRED system log)
find_package(PostgreSQL 9.5.12 REQUIRED)
find_package(libpqxx REQUIRED)
find_package(Threads REQUIRED)

# The main program
add_executable(DimensionServerTest ${test_files} ${project_files})
target_include_directories(DimensionServerTest PRIVATE ${Boost_INCLUDE_DIRS} ${LIBPQXX_INCLUDE_DIRS} ${thirdparty_INCLUDE_DIRS})
target_link_libraries(DimensionServerTest PRIVATE ${Boost_LIBRARIES} ${LIBPQXX_LIBRARY_DIRS} Threads::Threads catch2 json pybind11::embed)
