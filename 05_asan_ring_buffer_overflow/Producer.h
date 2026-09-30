#pragma once
#include "RingBuffer.h"

class Producer
{
public:
    explicit Producer(RingBuffer& ringBuffer) : m_ringBuffer(ringBuffer) {}
    void Run(int count);

private:
    RingBuffer& m_ringBuffer;
};