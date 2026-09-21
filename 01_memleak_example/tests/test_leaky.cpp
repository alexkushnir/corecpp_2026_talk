#include <gtest/gtest.h>
#include "leaky_calculator.h"
#include <vector>

// Test 1: Function compute_sum returns mathematically correct result.
TEST(LeakyCalculatorTest, ComputeSumReturnsCorrectValue) {
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    int expected_sum = 150;

    int actual_sum = leaky::compute_sum(numbers.data(), numbers.size());

    // Functional correctness check passes!
    EXPECT_EQ(actual_sum, expected_sum);
}

// Test 2: BufferProcessor processes data correctly.
TEST(BufferProcessorTest, HandlesMultipleInputsCorrectly) {
    leaky::BufferProcessor processor;

    processor.process(5);
    processor.process(15);
    processor.process(25);

    // Functional correctness check passes!
    EXPECT_EQ(processor.get_total(), 45);
}

// Test 3: Multiple calls to leaky function in a loop.
TEST(LeakyCalculatorTest, WorksRepeatedlyInLoop) {
    for (int i = 0; i < 1000; ++i) {
        std::vector<int> numbers = {i, i + 1, i + 2};
        int sum = leaky::compute_sum(numbers.data(), numbers.size());
        EXPECT_EQ(sum, 3 * i + 3);
    }
}
