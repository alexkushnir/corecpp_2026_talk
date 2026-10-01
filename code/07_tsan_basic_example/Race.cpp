bool stop = false; // plain bool

#include "poll.h"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void Poll()
{
    // Stand-in for real work: wait up to 10 ms for something to do.
    std::this_thread::sleep_for(10ms);
}

void Worker()
{
    while (!stop)
    {
        Poll();
    } // read
}

int main()
{
    std::thread t{Worker};
    std::this_thread::sleep_for(1s);
    stop = true; // write: race
    t.join();
}
// fix: std::atomic<bool> stop{false};