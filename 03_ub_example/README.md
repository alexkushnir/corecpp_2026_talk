# 03_ub_example

A minimal working example showing how traditional unit tests (e.g. GoogleTest) verify functional correctness and report **100% PASSED** (green) despite severe underlying Undefined Behavior (UB).

The unit under test uses signed integer overflow and bit shift out of bounds operations (adapted from the [gdb_workshop UBSan demo](https://github.com/alexkushnir/gdb_workshop/blob/master/day02/13_ubsan/main.cpp)).

## Overview

In traditional unit testing:
- Assertions (`EXPECT_EQ`, `ASSERT_TRUE`, etc.) evaluate output correctness.
- The test harness checks if code threw unhandled exceptions or crashed.
- **Undefined Behavior (UB) does NOT cause test failures by default!**

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
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from UBTest
[ RUN      ] UBTest.SignedIntegerOverflowPassesFunctionalCheck
Current value: 2147483647
Overflowed result: -2147483648
[       OK ] UBTest.SignedIntegerOverflowPassesFunctionalCheck (0 ms)
[ RUN      ] UBTest.ShiftOutOfBoundsPassesFunctionalCheck
Current value: 1, shift: 32
Shift result: 1
[       OK ] UBTest.ShiftOutOfBoundsPassesFunctionalCheck (0 ms)
[----------] 2 tests from UBTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
```

Notice that both tests pass green (`[ PASSED ] 2 tests.`), despite `compute_overflow` performing signed integer overflow and `compute_shift` shifting by 32 bits—both classic instances of Undefined Behavior (UB) in standard C++!
