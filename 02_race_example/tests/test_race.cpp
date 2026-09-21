#include <gtest/gtest.h>
#include "racing_counter.h"

class RacingCounterTest : public ::testing::Test {
protected:
    void SetUp() override {
        race::reset_counter();
    }
};

TEST_F(RacingCounterTest, SingleThreadWorkerFuncIncrementsCounter) {
    race::WorkerFunc(0, 1000);
    EXPECT_EQ(race::sharedCounter, 1000);
}

TEST_F(RacingCounterTest, ConcurrentWorkerThreadsPassFunctionalCheck) {
    race::run_workers(2, 100000);
    EXPECT_GT(race::sharedCounter, 0);
    EXPECT_LE(race::sharedCounter, 200000);
}

TEST_F(RacingCounterTest, ConcurrentWorkersCompleteWithoutCrash) {
    race::run_workers(2, 50000);
    SUCCEED();
}
