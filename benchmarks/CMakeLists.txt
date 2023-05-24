cmake_minimum_required(VERSION 3.8)
project(MyTest LANGUAGES C CXX)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

set(benchmark_DIR "C:/Users/Ryan/Documents/Git/AI-Library/external/googlebenchmark/build")
find_package(benchmark REQUIRED)

# Include the Google Benchmark headers
# Link against the Google Benchmark library
set(GOOGLEBENCH_ROOT "C:/Users/Ryan/Documents/Git/AI-Library/library_binaries")
include_directories(${GOOGLEBENCH_ROOT}/include)
link_directories(${GOOGLEBENCH_ROOT}/lib)

add_executable(MyTest main.cpp)
target_link_libraries(MyTest benchmark::benchmark)
target_link_libraries(MyTest "C:/Users/Ryan/Documents/Git/AI-Library/library_binaries/lib/AIL.lib")