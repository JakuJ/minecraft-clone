cmake_minimum_required(VERSION 3.16)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG  "-g")
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "--debug" "-g" "-ggdb"
)

find_package(glfw3 3.3 REQUIRED)

include_directories("include")
include_directories("headers")

file(GLOB app_libs "lib/*.c")
file(GLOB app_sources "src/*.cpp" "src/*/*.cpp")

add_executable(main ${app_libs} ${app_sources})

target_link_libraries(main glfw)