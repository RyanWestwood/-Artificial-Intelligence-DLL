cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
project(Tests)
set (CMAKE_CXX_STANDARD 20)
enable_testing()

# Find and include Google Test package
find_package(GTest REQUIRED PATHS ${PROJECT_SOURCE_DIR}/../library_binaries)

# `AddTest` to automate the process of adding unit tests
# Function parameters:
# - TestName: Name of the test executable
# - Sources: Source file(s) for the test
function(AddTest TestName Sources)
    add_executable(${TestName} ${Sources})  
    target_link_libraries(${TestName} GTest::gtest GTest::gtest_main)    
    target_include_directories(${TestName}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../source"
    )
    add_test(${TestName} ${TestName})
endfunction()

# Call the AddTest function to add the tests
AddTest(Test source/test.cpp)
AddTest(Test1 source/test-google-gtest.cpp)
