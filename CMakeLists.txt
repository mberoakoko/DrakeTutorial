cmake_minimum_required(VERSION 4.0)
project(DrakeTutorial)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)
find_package(Drake)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        # docking-latest
        GIT_TAG v1.91.8
)

add_subdirectory(vendor/imgui)
add_subdirectory(vendor/sdl)
add_subdirectory(vendor/implot)


add_executable(DrakeTutorial main.cpp
        src/examples/fibonnaci_diff_eqn/fib_ops.h
        src/examples/fibonnaci_diff_eqn/fib_runner.h
        src/plotting/plotter.hpp
        src/plotting/utills/plotter_primitives.hpp)
target_link_libraries(DrakeTutorial drake::drake SDL3::SDL3 imgui)

target_include_directories(DrakeTutorial
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${implot_SOURCE_DIR}
)