#include "ub_demo.h"
#include <iostream>
#include <limits>
#include <print>

namespace ub {

int compute_overflow(int val) {
    std::println("Current value: {}", val);
    // Undefined Behavior: Signed integer overflow
    int overflowed = val + 1;
    std::println("Overflowed result: {}", overflowed);
    return overflowed;
}

int compute_shift(int val, int shift) {
    std::println("Current value: {}, shift: {}", val, shift);
    // Undefined Behavior: Shift count >= width of type (32 bits)
    int result = val << shift;
    std::println("Shift result: {}", result);
    return result;
}

} // namespace ub
