#pragma once
#include <cstddef>

// Fixed-size ring buffer of ints: overwrites the oldest value when full.
class RingBuffer
{
public:
    explicit RingBuffer(std::size_t capacity);
    ~RingBuffer();
    RingBuffer(const RingBuffer&) = delete;
    RingBuffer& operator=(const RingBuffer&) = delete;

    void Push(int value);
    std::size_t Pushed() const
    {
        return m_pushed;
    }

private:
    int* m_data;
    std::size_t m_capacity;
    std::size_t m_head = 0;
    std::size_t m_pushed = 0;
};