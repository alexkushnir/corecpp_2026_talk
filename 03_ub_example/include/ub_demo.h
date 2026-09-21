#ifndef UB_DEMO_H
#define UB_DEMO_H

namespace ub {

// Triggers signed integer overflow: adding 1 to std::numeric_limits<int>::max()
int compute_overflow(int val);

// Triggers bit shift out of bounds: shifting 1 left by 32 bits on a 32-bit int
int compute_shift(int val, int shift);

} // namespace ub

#endif // UB_DEMO_H
