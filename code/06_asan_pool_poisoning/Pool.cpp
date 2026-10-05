#include "Pool.h"

#include <sanitizer/asan_interface.h> // macros are no-ops without ASan

Pool::Pool(std::size_t blocks)
    : m_chunk(new std::byte[blocks * sBlockSize]), m_size(blocks * sBlockSize)
{
    for (std::size_t i = 0; i < blocks; ++i)
    {
        m_free.push_back(m_chunk + i * sBlockSize);
    }
    // Nothing is handed out yet: the whole chunk is off-limits.
    ASAN_POISON_MEMORY_REGION(m_chunk, m_size);
}

Pool::~Pool()
{
    ASAN_UNPOISON_MEMORY_REGION(m_chunk, m_size);
    delete[] m_chunk;
}

void* Pool::Alloc()
{
    void* p = m_free.back();
    m_free.pop_back();
    // handed out: make it accessible
    ASAN_UNPOISON_MEMORY_REGION(p, sBlockSize);
    return p;
}

void Pool::Release(void* p)
{
    // returned: any access is now a bug
    ASAN_POISON_MEMORY_REGION(p, sBlockSize);
    m_free.push_back(p);
}