cmake_minimum_required(VERSION 3.28)
project(ubsan_optimizer CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_UBSAN "Build with UndefinedBehaviorSanitizer" OFF)

add_executable(ubsan_optimizer Ovf.cpp)

if(ENABLE_UBSAN)
  target_compile_options(ubsan_optimizer PRIVATE -fsanitize=undefined -fno-sanitize-recover=undefined -g -O0)
  target_link_options(ubsan_optimizer PRIVATE -fsanitize=undefined)
endif()