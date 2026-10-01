// TSan demo: Stats::Record() takes the mutex, Stats::Max() forgets to.
// The test passes; TSan reports a data race on m_max between the worker
// thread (holding the mutex) and the test thread (holding nothing).
#include <gtest/gtest.h>

#include "Worker.h"

TEST(Stats, MaxWhileWorkerRuns)
{
    Stats stats;
    Worker worker(stats);
    worker.Start(1000);
    int seen = stats.Max(); // races with Record
    worker.Join();
    EXPECT_LE(seen, 49);
    EXPECT_EQ(stats.Max(), 49);
}