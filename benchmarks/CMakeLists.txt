cmake_minimum_required(VERSION 3.8)
project(Benchmarks LANGUAGES C CXX)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(benchmark_DIR "${PROJECT_DIRECTORY}/external/googlebenchmark/build")
find_package(benchmark REQUIRED)

set(GOOGLEBENCH_ROOT "${PROJECT_DIRECTORY}/library_binaries")
include_directories(${GOOGLEBENCH_ROOT}/include)
link_directories(${GOOGLEBENCH_ROOT}/lib)

# Create program
add_executable(${PROJECT_NAME} main.cpp)

# Link the libraries 
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
target_link_libraries(${PROJECT_NAME} "${PROJECT_DIRECTORY}/library_binaries/lib/AIL.lib")

# Copy all the dll's required to run 
add_custom_command(TARGET Benchmarks
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../library_binaries/bin/AIL.dll ${AI_Benchmarks_BINARY_DIR}/.
)