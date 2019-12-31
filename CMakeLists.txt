cmake_minimum_required(VERSION 3.16)
project(openGLTut)

find_package(glfw3 3.3 REQUIRED)

include_directories("include")

add_executable(main main.cpp lib/glad.c)

target_link_libraries(main glfw)