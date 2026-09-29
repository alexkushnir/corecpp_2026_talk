// War story demo: a message pool recycles a buffer while a worker
// thread still holds a pointer to it.
//
//   Plain build : test passes; some messages are silently corrupted.
//   ASan build  : the pool falls back to new/delete, and ASan reports
//                 heap-use-after-free with the release() stack.
//   TSan build  : reports the race between the worker's read and the
//                 producer refilling the recycled buffer.

#include <gtest/gtest.h>

#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <mutex>
#include <thread>
#include <vector>

#if defined(__SANITIZE_ADDRESS__)
    #define POOL_USE_HEAP 1
#elif defined(__has_feature)
    #if __has_feature(address_sanitizer)
        #define POOL_USE_HEAP 1
    #endif
#endif

struct Message {
    std::uint32_t id;
    std::uint32_t checksum;
    unsigned char payload[56];
};

std::uint32_t checksum_of(const Message& m) {
    std::uint32_t sum = m.id;
    for (unsigned char b : m.payload) 
    {
        sum = sum * 31 + b;
    }

    return sum;
}

// Fixed-size pool: hands out recycled blocks instead of new/delete.
// Under ASan it uses real heap allocations so ASan can track lifetimes.
class MessagePool {
public:
    explicit MessagePool(std::size_t size) 
        : m_storage(size) {
        for (auto& m : m_storage) 
        { 
            m_free.push_back(&m);
        }
    }

    Message* acquire() {
#ifdef POOL_USE_HEAP
        return new Message{};
#else
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_free.empty())
        {
            return nullptr;
        } 

        Message* m = m_free.back();
        m_free.pop_back();

        return m;
#endif
}

    void release(Message* m) {
#ifdef POOL_USE_HEAP
        delete m;
#else
        std::lock_guard<std::mutex> lock(m_mutex);
        m_free.push_back(m);
#endif
    }

private:
    std::vector<Message> m_storage;
    std::vector<Message*> m_free;
    std::mutex m_mutex;
};

// Simple blocking queue of message pointers; nullptr means "stop".
class MessageQueue {
public:
    void push(Message* m) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push_back(m);
        }
    
        m_condVar.notify_one();
    }

    Message* pop() {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condVar.wait(lock, [&] { return !m_queue.empty(); });
            
        Message* m = m_queue.front();
        m_queue.pop_front();
            return m;
        }

private:
    std::deque<Message*> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
};

struct Stats {
    int processed = 0;
    int corrupted = 0;
};

Stats run_pipeline(int count) {
    MessagePool pool(4);
    MessageQueue queue;
    Stats stats;

    std::thread worker([&] {
        while (Message* m = queue.pop()) {
            std::this_thread::yield();            // simulate some work
            if (checksum_of(*m) != m->checksum)   // reads the message
            {
                ++stats.corrupted;
            }
            ++stats.processed;
        }
    });

    for (int i = 0; i < count; ++i) 
    {
        Message* m = nullptr;
        while ((m = pool.acquire()) == nullptr)
        {
            std::this_thread::yield();
        } 

        m->id = static_cast<std::uint32_t>(i);
        for (auto& b : m->payload) 
        {
            b = static_cast<unsigned char>(i);
        }
        
        m->checksum = checksum_of(*m);
        queue.push(m);
        pool.release(m);  // Bug: the worker still owns this message
    }

    queue.push(nullptr);
    worker.join();
    return stats;
}

TEST(Pipeline, ProcessesEveryMessage) {
    Stats stats = run_pipeline(10000);
    std::printf("processed=%d corrupted=%d\n", stats.processed, stats.corrupted);
    EXPECT_EQ(stats.processed, 10000);
}
