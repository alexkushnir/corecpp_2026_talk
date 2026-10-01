#pragma once
#include <mutex>

// Request statistics, updated by worker threads and read by a reporter.
class Stats
{
public:
    void Record(int latencyMs);
    long Count() const;
    int Max() const;

private:
    mutable std::mutex m_mutex;
    long m_count = 0;
    int m_max = 0;
};