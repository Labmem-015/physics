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

include(.cmake/export_compile_commands_to_root.cmake)

project(physics DESCRIPTION "Physics emulation using GPU" VERSION 0.1.0 LANGUAGES CXX)

file(GLOB hpp_files CONFIGURE_DEPENDS src/*.hpp)
file(GLOB cpp_files CONFIGURE_DEPENDS src/*.cpp)

add_executable(app ${hpp_files} ${cpp_files})
target_precompile_headers(app PUBLIC src/main.hpp)

find_package(raylib CONFIG REQUIRED)
#find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(app raylib) # glfw)

if(EXISTS "${PROJECT_SOURCE_DIR}/snippets/")
    add_subdirectory(snippets)
endif()
