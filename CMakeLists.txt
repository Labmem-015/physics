cmake_minimum_required(VERSION 3.31 FATAL_ERROR)
cmake_policy(VERSION 3.31)

set(CMAKE_LANG "en_US.UTF-8")

if(NOT DEFINED ENV{VCPKG_ROOT})
	message(FATAL_ERROR "VCPKG_ROOT is not defined!")
else()
    message("VCPKG_ROOT is defined: $ENV{VCPKG_ROOT}")
endif()

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_TOOLCHAIN_FILE)

project(physics DESCRIPTION "Physics emulation using GPU" VERSION 0.1.0 LANGUAGES CXX)

find_package(raylib CONFIG REQUIRED)
find_package(OpenCL CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

file(GLOB hpp_files CONFIGURE_DEPENDS src/*.hpp)
file(GLOB cpp_files CONFIGURE_DEPENDS src/*.cpp)

add_executable(app ${hpp_files} ${cpp_files})
target_precompile_headers(app PUBLIC src/main.hpp)
target_link_libraries(app raylib glfw)

if(EXISTS "${PROJECT_SOURCE_DIR}/snippets/")
    add_subdirectory(snippets)
endif()

if(EXISTS ${PROJECT_BINARY_DIR}/compile_commands.json)
    message("Copying ${PROJECT_BINARY_DIR}/compile_commands.json to root directory")
    file(COPY ${PROJECT_BINARY_DIR}/compile_commands.json DESTINATION ${PROJECT_SOURCE_DIR})
else()
    #message(WARNING "File ${PROJECT_BINARY_DIR}/compile_commands.json not found. Maybe this file didn't created yet, so reconfigure CMake project.")
endif()

