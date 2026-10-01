cmake_minimum_required(VERSION 3.28)

project(valgrind_basic_example CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(valgrind_basic_example parse.cpp)