#include <cstring>

struct Header
{
    int m_len;
    int m_flags;
};
int Parse(const char* buf)
{
    Header h; // not zeroed
    std::memcpy(&h.m_len, buf, 4);
    if (h.m_flags & 0x1) // uninit!
        return -1;
    return h.m_len;
}

int main()
{
    char buf[] = {0x01, 0x02, 0x03, 0x04};
    Parse(buf);

    return 0;
}