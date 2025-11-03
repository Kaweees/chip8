set(EXECUTABLE_NAME invaders)

file(GLOB_RECURSE PROJECT_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(PROJECT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${EXECUTABLE_NAME} ${PROJECT_SRCS})

# Add include directories
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_INCLUDES})

# Lyra
FetchContent_Declare(
  lyra
  GIT_REPOSITORY https://github.com/bfgroup/Lyra.git
  GIT_TAG "1.7.0"
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(lyra)

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${PROJECT_NAME} lyra)

# Setting our output directory
set_target_properties(
  ${EXECUTABLE_NAME}
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/target/release/"
             OUTPUT_NAME ${EXECUTABLE_NAME})
