cmake_minimum_required(VERSION 3.28)
project(asan_ring_buffer_overflow CXX)

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
 
add_executable(ring_buffer_tests RingBuffer.cpp Producer.cpp RingBufferTest.cpp)
target_link_libraries(ring_buffer_tests PRIVATE GTest::gtest_main)

if(ENABLE_ASAN)
  target_compile_options(ring_buffer_tests PRIVATE -fsanitize=address -fno-omit-frame-pointer -g -O1)
  target_link_options(ring_buffer_tests PRIVATE -fsanitize=address)
endif()

# Plain build: test passes.  -DENABLE_ASAN=ON: ASan reports heap-buffer-overflow.