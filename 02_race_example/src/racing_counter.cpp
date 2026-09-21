#include "racing_counter.h"
#include <iostream>
#include <print>
#include <pthread.h>
#include <string>
#include <thread>
#include <vector>

namespace race {

int sharedCounter = 0;

void reset_counter() {
    sharedCounter = 0;
}

void WorkerFunc(int id, int iterations) {
    std::string threadName = "Worker-" + std::to_string(id);
    pthread_setname_np(pthread_self(), threadName.c_str());

    std::println("[{}] Started.", threadName);

    for (int i = 0; i < iterations; ++i) {
        sharedCounter++;
    }

    std::println("[{}] Finished.", threadName);
}

void run_workers(std::size_t num_threads, int iterations_per_thread) {
    std::vector<std::jthread> threads;
    threads.reserve(num_threads);

    for (std::size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back(WorkerFunc, static_cast<int>(i), iterations_per_thread);
    }

    // std::jthread automatically joins upon destruction
}

} // namespace race
