project(DimensionServer_src)

message(\nRunning src CMakeLists.txt)
message(--------------------)

set(project_files
        ${CMAKE_SOURCE_DIR}/src/Network/Server.cpp
        ${CMAKE_SOURCE_DIR}/src/Network/Server.hpp
        ${CMAKE_SOURCE_DIR}/src/Network/Session.cpp
        ${CMAKE_SOURCE_DIR}/src/Network/Session.hpp
        CACHE INTERNAL "")

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.58.0 REQUIRED system log)
find_package(PostgreSQL 9.5.12 REQUIRED)
find_package(libpqxx REQUIRED)
find_package(Threads REQUIRED)

# The main program
add_executable(DimensionServer ${CMAKE_SOURCE_DIR}/src/main.cpp ${project_files})
target_include_directories(DimensionServer PRIVATE ${Boost_INCLUDE_DIRS} ${LIBPQXX_INCLUDE_DIRS})
target_link_libraries(DimensionServer PRIVATE ${Boost_LIBRARIES} ${LIBPQXX_LIBRARY_DIRS} Threads::Threads catch2 json pybind11)
