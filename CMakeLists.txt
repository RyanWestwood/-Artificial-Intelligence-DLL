cmake_minimum_required (VERSION 3.8)
project(AIL VERSION 1.0.0)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AIL)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOGGING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DLOGGING")

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCE "source/*.*")
foreach(SRC_FILE ${SOURCE})
  file(RELATIVE_PATH RELATIVE ${CMAKE_SOURCE_DIR} ${SRC_FILE})
  get_filename_component(SRC_FILE_DIR ${RELATIVE} DIRECTORY)
  source_group(${SRC_FILE_DIR} FILES ${SRC_FILE})
endforeach()

add_library(${PROJECT_NAME} SHARED ${SOURCE})

install(TARGETS ${PROJECT_NAME} EXPORT AI_LIBS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
    )

install(DIRECTORY include/ DESTINATION include/ai)
install(FILES README.md DESTINATION share/licenses/ai_lib)

option(TESTS "Run tests" ON)
if (TESTS MATCHES ON)
  # Enable building shared libraries
  option(BUILD_SHARED_LIBS "Build shared libraries" ON)
  # Enable creating a shared library for GTest
  option(GTEST_CREATE_SHARED_LIBRARY "Create a shared library for GTest" ON)
  add_subdirectory(external/googletest)
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  add_subdirectory(tests)
endif()