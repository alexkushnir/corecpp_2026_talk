# 02_race_example

A minimal working example showing how traditional unit tests (e.g. GoogleTest) verify functional correctness and report **100% PASSED** (green) despite severe underlying data races.

## Overview

In traditional unit testing:
- Assertions (`EXPECT_EQ`, `EXPECT_GE`, `ASSERT_TRUE`, etc.) evaluate output correctness.
- The test harness checks if code threw unhandled exceptions or crashed.
- **Data races do NOT cause test failures by default!**

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
[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from RacingCounterTest
[ RUN      ] RacingCounterTest.SingleThreadWorkerFuncIncrementsCounter
[Worker-0] Started.
[Worker-0] Finished.
[       OK ] RacingCounterTest.SingleThreadWorkerFuncIncrementsCounter (0 ms)
[ RUN      ] RacingCounterTest.ConcurrentWorkerThreadsPassFunctionalCheck
[Worker-0] Started.
[Worker-1] Started.
[Worker-0] Finished.
[Worker-1] Finished.
[       OK ] RacingCounterTest.ConcurrentWorkerThreadsPassFunctionalCheck (1 ms)
[ RUN      ] RacingCounterTest.ConcurrentWorkersCompleteWithoutCrash
[Worker-0] Started.
[Worker-1] Started.
[Worker-0] Finished.
[Worker-1] Finished.
[       OK ] RacingCounterTest.ConcurrentWorkersCompleteWithoutCrash (0 ms)
[----------] 3 tests from RacingCounterTest (1 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 3 tests.
```

Notice that all 3 tests pass green (`[ PASSED ] 3 tests.`), despite `WorkerFunc` invoking concurrent unsynchronized reads and writes on `sharedCounter`—a data race and Undefined Behavior (UB) according to the C++ memory model!
