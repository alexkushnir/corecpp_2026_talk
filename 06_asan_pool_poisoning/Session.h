#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "Pool.h"

// One client session. Incoming messages are stored in a pooled block.
class Session
{
public:
    explicit Session(Pool& pool);

    void Receive(const std::string& text);
    void Close();
    std::size_t LastSize() const;

private:
    struct Message
    {
        std::uint32_t m_size;
        char m_data[Pool::sBlockSize - sizeof(std::uint32_t)];
    };

    Pool& m_pool;
    Message* m_msg = nullptr;
};