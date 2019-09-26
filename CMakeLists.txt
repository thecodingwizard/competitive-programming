cmake_minimum_required(VERSION 3.9)
project(competitive-programming)

set(CMAKE_CXX_STANDARD 11)

# See https://stackoverflow.com/questions/43326924/increasing-stack-size-for-c-program-in-clion
MATH(EXPR stack_size "512 * 1024 * 1024") # 512 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(competitive-programming grader.cpp vision.cpp)