cmake_minimum_required(VERSION 3.28)
project(asan_pool_poisoning CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_ASAN "Build with AddressSanitizer" OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.18.0
  GIT_SHALLOW    TRUE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(pool_tests Pool.cpp Session.cpp SessionTest.cpp)
target_link_libraries(pool_tests PRIVATE GTest::gtest_main)

if(ENABLE_ASAN)
  target_compile_options(pool_tests PRIVATE -fsanitize=address -fno-omit-frame-pointer -g -O1)
  target_link_options(pool_tests PRIVATE -fsanitize=address)
endif()
