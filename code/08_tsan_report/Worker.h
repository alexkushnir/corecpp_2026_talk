#pragma once
#include <thread>

#include "Stats.h"

// Handles requests on its own thread and records their latency.
class Worker
{
public:
    explicit Worker(Stats& stats);
    void Start(int requests);
    void Join();

private:
    void Run(int requests);

    Stats& m_stats;
    std::thread m_thread;
};