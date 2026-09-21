# 01_memleak_example

A minimal working example showing how traditional unit tests (e.g. GoogleTest) verify functional correctness and report **100% PASSED** (green) despite severe underlying memory leaks.

## Overview

In traditional unit testing:
- Assertions (`EXPECT_EQ`, `ASSERT_TRUE`, etc.) evaluate output correctness.
- The test harness checks if code threw unhandled exceptions or crashed.
- **Memory leaks do NOT cause test failures by default!**

This repository demonstrates this phenomenon with C++23.

## How to Build & Run Tests

```bash
# Configure build with CMake
cmake -B build -S .

# Build the targets
cmake --build build

# Run unit tests via CTest
ctest --test-dir build --output-on-failure

# Alternatively, execute the test binary directly:
./build/unit_tests
```

### Expected Output

Running `./build/unit_tests` will produce output similar to:

```text
[==========] Running 3 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from LeakyCalculatorTest
[ RUN      ] LeakyCalculatorTest.ComputeSumReturnsCorrectValue
[       OK ] LeakyCalculatorTest.ComputeSumReturnsCorrectValue (0 ms)
[ RUN      ] LeakyCalculatorTest.WorksRepeatedlyInLoop
[       OK ] LeakyCalculatorTest.WorksRepeatedlyInLoop (1 ms)
[----------] 2 tests from LeakyCalculatorTest (1 ms total)

[----------] 1 test from BufferProcessorTest
[ RUN      ] BufferProcessorTest.HandlesMultipleInputsCorrectly
[       OK ] BufferProcessorTest.HandlesMultipleInputsCorrectly (0 ms)
[----------] 1 test from BufferProcessorTest (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test suites ran. (1 ms total)
[  PASSED  ] 3 tests.
```

Notice that all 3 tests pass green (`[ PASSED ] 3 tests.`), despite `compute_sum` and `BufferProcessor` leaking memory on every invocation!

