#pragma once

#include <cstdint>

class Session
{
public:
    explicit Session(int id);
    int Id() const;

private:
    std::uint64_t m_created = 0;
    std::uint64_t m_lastSeen = 0;
    int m_id;
    char m_buffer[44] = {}; // sizeof(Session) == 64
};
