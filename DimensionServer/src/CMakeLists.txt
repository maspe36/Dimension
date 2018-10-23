project(DimensionServer_src)

message(\nRunning src CMakeLists.txt)
message(--------------------)

set(project_files
        ${CMAKE_SOURCE_DIR}/src/Network/Server.cpp
        ${CMAKE_SOURCE_DIR}/src/Network/Server.hpp
        ${CMAKE_SOURCE_DIR}/src/Network/Client.cpp
        ${CMAKE_SOURCE_DIR}/src/Network/Client.hpp
        CACHE INTERNAL "")

# All sources that also need to be tested in unit tests go into a static library
add_library(DimensionServerLib STATIC ${project_files} ../test/CatchMain.cpp)
target_include_directories(DimensionServerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.58.0 REQUIRED system log)
find_package(PostgreSQL 9.5.12 REQUIRED)
find_package(libpqxx REQUIRED)
find_package(Threads REQUIRED)

# The main program
add_executable(DimensionServer ${CMAKE_SOURCE_DIR}/src/main.cpp ${project_files})
target_include_directories(DimensionServer PRIVATE ${Boost_INCLUDE_DIRS} ${LIBPQXX_INCLUDE_DIRS})
target_link_libraries(DimensionServer PRIVATE ${Boost_LIBRARIES} ${LIBPQXX_LIBRARY_DIRS} Threads::Threads)
