cmake_minimum_required(VERSION 3.10)
project(SDL_3D_Graphics)

set(CMAKE_CXX_STANDARD 14)

# Non GUI
set(CMAKE_EXE_LINKER_FLAGS "-mconsole")  # Console App

# SDL2 Files
include_directories(${CMAKE_SOURCE_DIR}/SDL2/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Centralized build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/cmake)

# CMake Output Directories (auto-generated)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Executable
add_executable(SDL_3D_Graphics src/main.cpp
        include/screen.hpp)

# SDL2 and dll with the executable
target_link_libraries(SDL_3D_Graphics
        ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib
)

add_custom_command(TARGET SDL_3D_Graphics POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/SDL2/lib/x64/SDL2.dll
        $<TARGET_FILE_DIR:SDL_3D_Graphics>  # Copy the dll to the same directory as the executable
)

# Type of build
set(CMAKE_BUILD_TYPE Debug)