#include "Worker.h"

Worker::Worker(Stats& stats) : m_stats(stats) {}

void Worker::Start(int requests)
{
    m_thread = std::thread(&Worker::Run, this, requests);
}

void Worker::Join()
{
    m_thread.join();
}

void Worker::Run(int requests)
{
    for (int i = 0; i < requests; ++i)
    {
        m_stats.Record(i % 50); // 0..49 ms
    }
}