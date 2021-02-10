cmake_minimum_required(VERSION 3.12.4)
project(MinecraftClone)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(LINUX (UNIX AND NOT APPLE))

find_package(glfw3 REQUIRED)

include_directories("include")
include_directories("external")

# Main executable
add_compile_options("-fexceptions" "-O3" "-flto")
# Linux GitHub Actions environment hates casting to function pointers and my logs are full of warnings
if (NOT LINUX)
    add_compile_options("-Wall" "-Wextra" "-Wpedantic")
endif ()

file(GLOB_RECURSE app_sources "src/*.cpp")
add_executable(App ${app_sources})

# Strip the produced binary
set_target_properties(App PROPERTIES LINK_FLAGS_RELEASE -s)

# The GLAD library
add_library(glad STATIC "external/glad/glad.c")

# The stb_image library
add_library(stb_image STATIC "external/stb/stb_image.c")

# The FastNoiseSIMD library
add_compile_options("-mfma" "-Wno-unused-parameter" "-Wno-sometimes-uninitialized")
set_source_files_properties("external/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp" PROPERTIES COMPILE_FLAGS "-msse2")
set_source_files_properties("external/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp" PROPERTIES COMPILE_FLAGS "-msse4.1")
set_source_files_properties("external/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp" PROPERTIES COMPILE_FLAGS "-mavx2")

file(GLOB noise_sources "external/FastNoiseSIMD/*.cpp")
add_library(FastNoiseSIMD SHARED ${noise_sources})

# Link libpthread on Linux
if (LINUX)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    find_package(Threads REQUIRED)
    target_link_libraries(App Threads::Threads) # ${CMAKE_THREAD_LIBS_INIT}
endif ()

target_link_libraries(App glfw glad FastNoiseSIMD stb_image)

# Generate updated PlantUML diagram
add_custom_command(
        TARGET App
        POST_BUILD COMMAND tools/generate_uml.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        BYPRODUCTS docs/class_diagram.puml
)

# Set up dylib RPATH on macOS
if (APPLE)
    set_target_properties(App PROPERTIES INSTALL_RPATH "lib")
endif ()

set(CMAKE_INSTALL_PREFIX "installed")

# Install binaries
install(TARGETS App glad stb_image FastNoiseSIMD
        RUNTIME DESTINATION .
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

# Copy application data
install(DIRECTORY "data" DESTINATION ".")
