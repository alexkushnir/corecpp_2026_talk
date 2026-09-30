#include "RingBuffer.h"

RingBuffer::RingBuffer(std::size_t capacity) : m_data(new int[capacity]), m_capacity(capacity) {}

RingBuffer::~RingBuffer()
{
    delete[] m_data;
}

void RingBuffer::Push(int value)
{
    m_data[m_head] = value; // writes m_data[m_capacity] once per lap
    ++m_pushed;
    if (++m_head > m_capacity) // BUG: should be >=
    { 
        m_head = 0;
    }
}
