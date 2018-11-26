project(DimensionServer_src)

message("\nRunning src CMakeLists.txt")
message(--------------------)

add_subdirectory(Python)

set(project_files
        ${CMAKE_SOURCE_DIR}/src/Game/Card.cpp
        ${CMAKE_SOURCE_DIR}/src/Game/Card.hpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Client.cpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Client.hpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Connection.cpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Connection.hpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Handlers.cpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Handlers.hpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Lobby.cpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Lobby.hpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/ResponseFunctionHelper.hpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Server.cpp
        ${CMAKE_SOURCE_DIR}/src/Network-TCP/Server.hpp
        ${CMAKE_SOURCE_DIR}/src/Python/Helpers.cpp
        ${CMAKE_SOURCE_DIR}/src/Python/Helpers.hpp
        CACHE INTERNAL "")

find_package(Threads REQUIRED)

# The main program
add_executable(DimensionServer ${CMAKE_SOURCE_DIR}/src/main.cpp ${project_files})
target_include_directories(DimensionServer PRIVATE ${thirdparty_includes})
target_link_libraries(DimensionServer PRIVATE ${thirdparty_libs})
