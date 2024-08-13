cmake_minimum_required(VERSION 3.13)
project(glengine)

add_executable(test)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


target_link_libraries(test PRIVATE glfw)
target_link_libraries(test PRIVATE GLEW)
target_link_libraries(test PRIVATE X11)
target_link_libraries(test PRIVATE GL)
target_link_libraries(test PRIVATE pthread)
target_link_libraries(test PRIVATE Xrandr)
target_link_libraries(test PRIVATE Xi)
target_link_libraries(test PRIVATE dl)


add_subdirectory(src)
target_include_directories(test PRIVATE "src/")
target_include_directories(test PRIVATE "include/")

#set(GCC_COVERAGE_LINK_FLAGS "-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW")

SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_custom_target(assets 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(test assets)
