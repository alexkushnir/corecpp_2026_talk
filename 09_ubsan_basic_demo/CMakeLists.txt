cmake_minimum_required(VERSION 3.28)
project(ubsan_basic_demo CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_ASAN "Build with AddressSanitizer" OFF)
option(ENABLE_UBSAN "Build with UndefinedBehaviorSanitizer" OFF)

add_executable(ubsan_basic_demo Header.cpp)

if(ENABLE_ASAN)
  target_compile_options(ubsan_basic_demo PRIVATE -fsanitize=address -fno-omit-frame-pointer -g -O1)
  target_link_options(ubsan_basic_demo PRIVATE -fsanitize=address)
endif()

if(ENABLE_UBSAN)
  target_compile_options(ubsan_basic_demo PRIVATE -fsanitize=undefined -fno-sanitize-recover=undefined -g -O1)
  target_link_options(ubsan_basic_demo PRIVATE -fsanitize=undefined)
endif()