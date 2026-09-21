#include "leaky_calculator.h"
#include <numeric>
#include <algorithm>

namespace leaky {

int compute_sum(const int* data, std::size_t count) {
    if (count == 0 || data == nullptr) {
        return 0;
    }

    // Dynamic allocation that is NEVER deleted -> Memory Leak!
    int* temp_copy = new int[count];
    for (std::size_t i = 0; i < count; ++i) {
        temp_copy[i] = data[i];
    }

    int sum = 0;
    for (std::size_t i = 0; i < count; ++i) {
        sum += temp_copy[i];
    }

    // Notice: missing `delete[] temp_copy;`
    return sum;
}

BufferProcessor::BufferProcessor() 
    : m_capacity(16), m_size(0) {
    // Dynamic allocation in constructor
    m_buffer = new int[m_capacity];
}

BufferProcessor::~BufferProcessor() {
    // Intentionally empty destructor: memory allocated in constructor is leaked!
}

void BufferProcessor::process(int value) {
    if (m_size < m_capacity) {
        m_buffer[m_size++] = value;
        m_total += value;
    }
}

int BufferProcessor::get_total() const {
    return m_total;
}

} // namespace leaky
