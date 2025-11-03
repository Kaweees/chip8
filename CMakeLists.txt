cmake_minimum_required(VERSION 3.30 FATAL_ERROR) # Set the minimum required
                                                 # version of CMake

project(
  chip8
  VERSION 1.0.0
  LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -pipe -fopenmp")

# Library target
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)

include(FetchContent)

# Raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
  GIT_TAG "master"
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(raylib)

# Link libraries
target_link_libraries(${PROJECT_NAME} INTERFACE raylib)

# Optional builds
option(CHIP8_BUILD_EXAMPLES "Build examples" ON)

# Examples
if(CHIP8_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
