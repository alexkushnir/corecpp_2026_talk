#pragma once
#include <cstddef>
#include <vector>

// Fixed-size block pool: one heap chunk, handed out in kBlock-byte pieces.
// ASan only sees the chunk, so the pool poisons blocks it does not own.
class Pool {
  public:
    static constexpr std::size_t s_BlockSize = 64;  // multiple of 8 (shadow granularity)

    explicit Pool(std::size_t blocks);
    ~Pool();
    Pool(const Pool&) = delete;
    Pool& operator=(const Pool&) = delete;

    void* Alloc();
    void Release(void* p);

  private:
    std::byte* m_chunk;
    std::size_t m_size;
    std::vector<void*> m_free;  // kept outside the blocks, never poisoned
};