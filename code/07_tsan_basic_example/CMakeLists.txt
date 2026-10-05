cmake_minimum_required(VERSION 3.28)
project(tsan_basic_example CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TSAN "Build with ThreadSanitizer" OFF)

add_executable(tsan_basic_example Race.cpp)

if(ENABLE_TSAN)
  target_compile_options(tsan_basic_example PRIVATE -fsanitize=thread -g -O1)
  target_link_options(tsan_basic_example PRIVATE -fsanitize=thread)
endif()
