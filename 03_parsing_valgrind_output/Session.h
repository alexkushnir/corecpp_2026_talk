#pragma once

#include <cstdint>
 
class Session {
public:
    explicit Session(int id);
    int id() const;

private:
    std::uint64_t m_created = 0;
    std::uint64_t m_last_seen = 0;
    int m_id;
    char m_buffer[44] = {};  // sizeof(Session) == 64
};
 