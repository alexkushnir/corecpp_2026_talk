cmake_minimum_required(VERSION 3.16)
project(war_story_intro CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -DSANITIZER=address | thread | (empty for a plain build)
set(SANITIZER "" CACHE STRING "Sanitizer to enable: address, thread, or empty")

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

add_executable(war_story_intro pool_use_after_free.cpp)
target_link_libraries(war_story_intro PRIVATE GTest::gtest_main)

if(SANITIZER)
  target_compile_options(war_story_intro PRIVATE
    -fsanitize=${SANITIZER} -fno-omit-frame-pointer -g)
  target_link_options(war_story_intro PRIVATE -fsanitize=${SANITIZER})
endif()
