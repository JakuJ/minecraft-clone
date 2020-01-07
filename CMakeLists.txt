cmake_minimum_required(VERSION 3.12.4)
project(MinecraftClone)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

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
include_directories("headers")

# Main executable
add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "-O3" "-flto"
)
if (LINUX)
  set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
  find_package(Threads REQUIRED)
endif ()

file(GLOB app_sources "src/*.cpp" "src/*/*.cpp")
add_executable(App ${app_sources})

# Strip the produced binary
set_target_properties(App PROPERTIES LINK_FLAGS_RELEASE -s)

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

# Link libpthread on Linux
if(LINUX)
target_link_libraries(App glfw glad FastNoiseSIMD stb_image ${CMAKE_THREAD_LIBS_INIT})
else()
target_link_libraries(App LINK_PUBLIC glfw glad FastNoiseSIMD stb_image)
endif()


if(APPLE) # Set up dylib RPATH on macOS
set_target_properties(App PROPERTIES INSTALL_RPATH "lib")
elseif(LINUX)
set(CMAKE_INSTALL_PREFIX "../instdir")
endif()

# Install binaries
install(TARGETS App glad stb_image FastNoiseSIMD
        RUNTIME DESTINATION .
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

# Copy application data
file(GLOB shader_files "data/shaders/*")
file(GLOB texture_files "data/textures/*.png")

install(FILES ${shader_files} DESTINATION "data/shaders")
install(FILES ${texture_files} DESTINATION "data/textures")
