cmake_minimum_required(VERSION 3.8)
project(Tests)
set (CMAKE_CXX_STANDARD 20)
enable_testing()

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

AddTest(Test source/test.cpp)
AddTest(Test1 source/test-google-gtest.cpp)
