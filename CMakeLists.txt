cmake_minimum_required(VERSION 3.13)

project(bezier-curves)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/glfw)

add_executable(
    ${PROJECT_NAME}

    src/main.cpp
    src/window.cpp

    src/window.hpp
)

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE deps/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/precompiled.hpp)
