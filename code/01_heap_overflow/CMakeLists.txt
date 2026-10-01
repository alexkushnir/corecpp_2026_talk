cmake_minimum_required(VERSION 3.28)
project(heap_overflow CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_executable(heap_overflow heap_overflow.cpp)

if (ENABLE_ASAN)
  target_compile_options(heap_overflow PRIVATE -fsanitize=address)
  target_link_options(heap_overflow PRIVATE -fsanitize=address)
endif()

target_link_libraries(heap_overflow PRIVATE GTest::gtest_main)

# Keep ASan reports short: no shadow byte legend, short alloc/free stacks, function names only
gtest_discover_tests(heap_overflow
  PROPERTIES ENVIRONMENT 
  "ASAN_OPTIONS=print_legend=0:malloc_context_size=7:stack_trace_format='    #%n %f'"
)
