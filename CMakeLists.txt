cmake_minimum_required(VERSION 3.13)
project(glengine)

add_executable(test)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_library(glfw glfw3 HINTS /usr/lib/)
find_library(glew1 GLEW HINTS /usr/lib/)

if(NOT glfw)
  message(FATAL_ERROR "gl library not found")
endif()

add_subdirectory(src)
target_include_directories(test PRIVATE "src/")
target_include_directories(test PRIVATE "include/")

set(GCC_COVERAGE_LINK_FLAGS "-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_custom_target(assets 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(test assets)
