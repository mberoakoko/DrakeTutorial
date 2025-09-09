cmake_minimum_required(VERSION 4.0)
project(DrakeTutorial)

set(CMAKE_CXX_STANDARD 23)
find_package(Drake)

add_executable(DrakeTutorial main.cpp
        src/examples/fibonnaci_diff_eqn/fib_ops.h
        src/examples/fibonnaci_diff_eqn/fib_runner.h)
target_link_libraries(DrakeTutorial drake::drake)