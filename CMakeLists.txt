cmake_minimum_required(VERSION 3.16)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "-g" "-ggdb"
)

find_package(glfw3 3.3 REQUIRED)

include_directories("include")
include_directories("headers")

file(GLOB app_libs "lib/*.c")
file(GLOB app_sources "src/*.cpp" "src/buffers/*.cpp" "src/world/*.cpp")

add_executable(main ${app_libs} ${app_sources})

target_link_libraries(main glfw)