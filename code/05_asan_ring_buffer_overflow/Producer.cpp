#include "Producer.h"

void Producer::Run(int count)
{
    for (int i = 0; i < count; ++i)
    {
        m_ringBuffer.Push(i);
    }
}