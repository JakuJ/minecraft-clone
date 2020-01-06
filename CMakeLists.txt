cmake_minimum_required(VERSION 3.16)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR "bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(glfw3 3.3 REQUIRED)

include_directories("include")
include_directories("headers")

# Main executable
add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "-O3" "-flto"
)

file(GLOB app_sources "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")
add_executable(main ${app_sources})

# The GLAD library
add_library(glad STATIC "lib/glad.c")

# The stb_image library
add_library(stb_image STATIC "lib/stb_image.c")

# The FastNoiseSIMD library
add_compile_options("-mfma" "-Wno-unused-parameter" "-Wno-sometimes-uninitialized")

set_source_files_properties("lib/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp" PROPERTIES COMPILE_FLAGS "-msse2")
set_source_files_properties("lib/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp" PROPERTIES COMPILE_FLAGS "-msse4.1")
set_source_files_properties("lib/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp" PROPERTIES COMPILE_FLAGS "-mavx2")

file(GLOB noise_sources "lib/FastNoiseSIMD/*.cpp")
add_library(FastNoiseSIMD SHARED ${noise_sources})

target_link_libraries(main glfw glad stb_image FastNoiseSIMD)