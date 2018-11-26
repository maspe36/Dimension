project(DimensionServer_src)

message("\nRunning src CMakeLists.txt")
message(--------------------)

add_subdirectory(Python)

set(project_files
        ${CMAKE_SOURCE_DIR}/src/Game/Card.cpp
        ${CMAKE_SOURCE_DIR}/src/Game/Card.hpp
        ${CMAKE_SOURCE_DIR}/src/Python/Helpers.cpp
        ${CMAKE_SOURCE_DIR}/src/Python/Helpers.hpp
        CACHE INTERNAL "")

find_package(Threads REQUIRED)

# The main program
add_executable(DimensionServer ${CMAKE_SOURCE_DIR}/src/main.cpp ${project_files})
target_include_directories(DimensionServer PRIVATE ${thirdparty_includes})
target_link_libraries(DimensionServer PRIVATE ${thirdparty_libs})
