project(DimensionServer_test)

message("\nRunning test CMakeLists.txt")
message(--------------------)

set(test_files
        CatchMain.cpp
        Python/test_Interpreter.cpp)

find_package(Threads REQUIRED)

# The main program
add_executable(DimensionServerTest ${test_files} ${project_files})
target_include_directories(DimensionServerTest PRIVATE ${thirdparty_includes})
target_link_libraries(DimensionServerTest PRIVATE ${thirdparty_libs})
