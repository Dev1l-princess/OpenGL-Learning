cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME OpenGL-Learning)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} core/main.cpp)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)