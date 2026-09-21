cmake_minimum_required(VERSION 3.20)
project(02_race_example CXX)

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

# Library target with data race
add_library(race_lib src/racing_counter.cpp)
target_include_directories(race_lib PUBLIC include)

# Unit test executable target
add_executable(unit_tests tests/test_race.cpp)
target_link_libraries(unit_tests PRIVATE race_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
