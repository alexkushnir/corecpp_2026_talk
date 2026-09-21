#ifndef RACING_COUNTER_H
#define RACING_COUNTER_H

#include <cstddef>

namespace race {

// Shared variable without synchronization to trigger a data race
extern int sharedCounter;

// Resets shared counter to 0
void reset_counter();

// Worker function setting thread name and incrementing shared counter
void WorkerFunc(int id, int iterations = 100000);

// Runs concurrent worker threads calling WorkerFunc
void run_workers(std::size_t num_threads = 2, int iterations_per_thread = 100000);

} // namespace race

#endif // RACING_COUNTER_H
