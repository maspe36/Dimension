project(DimensionServer_python)

message("\nRunning src/Python CMakeLists.txt")
message(--------------------)

pybind11_add_module(Game
        ${CMAKE_SOURCE_DIR}/src/Python/Module.cpp
        ${CMAKE_SOURCE_DIR}/src/Game/Card.cpp)
