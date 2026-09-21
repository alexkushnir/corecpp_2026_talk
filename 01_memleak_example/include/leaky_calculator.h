#ifndef LEAKY_CALCULATOR_H
#define LEAKY_CALCULATOR_H

#include <cstddef>

namespace leaky {

// Computes the sum of elements, but internally allocates dynamic memory without freeing it.
int compute_sum(const int* data, std::size_t count);

// A simple structure that leaks memory upon processing.
class BufferProcessor {
public:
    BufferProcessor();
    ~BufferProcessor(); // Intentionally does not free allocated memory!

    void process(int value);
    [[nodiscard]] int get_total() const;

private:
    int* m_buffer;
    std::size_t m_capacity;
    std::size_t m_size;
    int m_total{0};
};

} // namespace leaky

#endif // LEAKY_CALCULATOR_H
