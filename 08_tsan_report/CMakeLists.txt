cmake_minimum_required(VERSION 3.28)
project(tsan_stats_race CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TSAN "Build with ThreadSanitizer" OFF)

add_executable(stats_tests stats.cpp worker.cpp stats_test.cpp)
target_link_libraries(stats_tests PRIVATE GTest::gtest_main Threads::Threads)

if(ENABLE_TSAN)
  target_compile_options(stats_tests PRIVATE -fsanitize=thread -g -O1)
  target_link_options(stats_tests PRIVATE -fsanitize=thread)
endif()

# Plain build: test passes.
# -DENABLE_TSAN=ON: TSan reports a data race on Stats::m_max.