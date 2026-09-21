cmake_minimum_required(VERSION 3.20)
project(01_memleak_example CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch GoogleTest framework
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Leaky library target
add_library(leaky_lib src/leaky_calculator.cpp)
target_include_directories(leaky_lib PUBLIC include)

# Unit test executable target
add_executable(unit_tests tests/test_leaky.cpp)
target_link_libraries(unit_tests PRIVATE leaky_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
