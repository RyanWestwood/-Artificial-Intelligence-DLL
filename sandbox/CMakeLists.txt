cmake_minimum_required (VERSION 3.8)
project(Sandbox VERSION 1.0.0)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set (CMAKE_CXX_STANDARD 20)

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

# Create program
add_executable(${PROJECT_NAME} ${SOURCE})

# Find SDL and SDLImage
find_package(SDL2 REQUIRED PATHS ${PROJECT_SOURCE_DIR}/../library_binaries)
find_package(SDL2_IMAGE REQUIRED PATHS ${PROJECT_SOURCE_DIR}/../library_binaries)

# Set library files 
set(LIB_FILES 
    "${SDL2_LIBRARIES}"
    "${PROJECT_SOURCE_DIR}/../library_binaries/lib/SDL2_image.lib"
    $<IF:$<CONFIG:Debug>,${PROJECT_SOURCE_DIR}/../library_binaries/lib/dAIL.lib,${PROJECT_SOURCE_DIR}/../library_binaries/lib/AIL.lib>
) 

# Specify output directories for different build configurations
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release
)

# Copy all the dll's required to run 
add_custom_command(TARGET Sandbox
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
      $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/Debug/.,${CMAKE_BINARY_DIR}/Release/.>
      ${Sandbox_BINARY_DIR}/.
  COMMAND ${CMAKE_COMMAND} -E copy 
      ${PROJECT_SOURCE_DIR}/../library_binaries/bin/SDL2_image.dll 
      $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/Debug/.,${CMAKE_BINARY_DIR}/Release/.>

  # Conditional copying for AIL.dll based on the build configuration
  COMMAND ${CMAKE_COMMAND} -E copy 
  $<IF:$<CONFIG:Debug>,${PROJECT_SOURCE_DIR}/../library_binaries/bin/Debug/dAIL.dll,${PROJECT_SOURCE_DIR}/../library_binaries/bin/AIL.dll> 
  $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/Debug/.,${CMAKE_BINARY_DIR}/Release/.>
)

# Library directory includes and linking
include_directories(${PROJECT_SOURCE_DIR}/../library_binaries/include)
target_link_libraries(${PROJECT_NAME} ${LIB_FILES})