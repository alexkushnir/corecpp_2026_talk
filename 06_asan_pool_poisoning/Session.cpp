#include "Session.h"

#include <algorithm>
#include <cstring>

Session::Session(Pool& pool) : m_pool(pool) {}

void Session::Receive(const std::string& text)
{
    if (m_msg == nullptr)
    {
        m_msg = static_cast<Message*>(m_pool.Alloc());
    }
    m_msg->m_size = static_cast<std::uint32_t>(std::min(text.size(), sizeof(m_msg->m_data)));
    std::memcpy(m_msg->m_data, text.data(), m_msg->m_size);
}

void Session::Close()
{
    m_pool.Release(m_msg); // bug: m_msg is not reset to nullptr
}

std::size_t Session::LastSize() const
{
    return m_msg->m_size; // reads a block that was already released
}