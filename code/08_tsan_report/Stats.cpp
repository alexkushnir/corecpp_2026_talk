#include "Stats.h"

void Stats::Record(int latencyMs)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    ++m_count;
    if (latencyMs > m_max)
    {
        m_max = latencyMs;
    }
}

long Stats::Count() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_count;
}

int Stats::Max() const
{
    return m_max;
}