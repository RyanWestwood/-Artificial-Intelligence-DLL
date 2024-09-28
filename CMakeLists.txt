cmake_minimum_required (VERSION 3.8)
project(AIL VERSION 1.0.0)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AIL)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Set flags for logging in Debug and RelWithDebugInfo
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOGGING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DLOGGING")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect source and header files
file(GLOB_RECURSE SOURCE "source/*.*")
file(GLOB_RECURSE HEADERS "include/*.*")

# Organize source files into folders based on their directory
foreach(SRC_FILE ${SOURCE} ${HEADERS})
  file(RELATIVE_PATH RELATIVE ${CMAKE_SOURCE_DIR} ${SRC_FILE})
  get_filename_component(SRC_FILE_DIR ${RELATIVE} DIRECTORY)
  source_group(${SRC_FILE_DIR} FILES ${SRC_FILE})
endforeach()

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCE} ${HEADERS})

# Specify output directories for different build configurations
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin
    OUTPUT_NAME_DEBUG "d${PROJECT_NAME}"  # dAIL.dll for Debug
    OUTPUT_NAME_RELEASE "${PROJECT_NAME}" # AIL.dll for Release
)

# Define options for each subdirectory
option(BUILD_SANDBOX "Build Sandbox" ON)
option(BUILD_BENCHMARKS "Build Benchmarks" ON)
option(BUILD_TESTS "Build Tests" OFF)

# Conditionally add subdirectories based on the options
if(BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Install targets for Debug and Release
install(TARGETS ${PROJECT_NAME} EXPORT AI_LIBS
    CONFIGURATIONS Debug Release
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin/$<IF:$<CONFIG:Debug>,Debug,>
    PUBLIC_HEADER DESTINATION include
    )

# Install headers and other files
install(DIRECTORY include/ DESTINATION include/ai)
install(FILES README.md DESTINATION share/licenses/ai_lib)