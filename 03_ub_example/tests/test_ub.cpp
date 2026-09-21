#include <gtest/gtest.h>
#include <limits>
#include "ub_demo.h"

TEST(UBTest, SignedIntegerOverflowPassesFunctionalCheck) {
    int max_int = std::numeric_limits<int>::max();
    int result = ub::compute_overflow(max_int);

    // Standard unit test assertions check numerical output (e.g. wrapped value on x86_64).
    // Standard test runners evaluate boolean assertions and do NOT detect language-level Undefined Behavior.
    // GoogleTest marks this test [ PASSED ] green!
    EXPECT_EQ(result, std::numeric_limits<int>::min());
}

TEST(UBTest, ShiftOutOfBoundsPassesFunctionalCheck) {
    int result = ub::compute_shift(1, 32);

    // Unit test completes without crashing and passes assertion checks.
    EXPECT_EQ(result, 1);
}
