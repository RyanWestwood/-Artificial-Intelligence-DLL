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

# Set library files 
set(LIB_FILES 
    benchmark::benchmark
    $<IF:$<CONFIG:Debug>,${PROJECT_SOURCE_DIR}/../library_binaries/lib/dAIL.lib,${PROJECT_SOURCE_DIR}/../library_binaries/lib/AIL.lib>
) 

# Specify output directories for different build configurations
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
)

# Copy all the dll's required to run 
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  # Conditional copying for AIL.dll based on the build configuration
  COMMAND ${CMAKE_COMMAND} -E copy 
  $<IF:$<CONFIG:Debug>,${PROJECT_SOURCE_DIR}/../library_binaries/bin/Debug/dAIL.dll,${PROJECT_SOURCE_DIR}/../library_binaries/bin/AIL.dll> 
  $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/Debug/.,${CMAKE_BINARY_DIR}/Release/.>
)

# Library directory includes and linking
target_link_libraries(${PROJECT_NAME} ${LIB_FILES})
include_directories(${GOOGLEBENCH_ROOT}/include)
link_directories(${GOOGLEBENCH_ROOT}/lib)