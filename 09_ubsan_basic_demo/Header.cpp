#include <cstdint>
#include <print>

struct Header
{
    char m_tag[4];
    std::uint32_t m_length;
};

void SetTag(Header& h, const char* tag)
{
    for (int i = 0; i <= 4; ++i)
    { // copies the '\0' too
        h.m_tag[i] = tag[i];
    }
}

int main()
{
    Header h{{}, 0x12345678};
    SetTag(h, "DATA");
    std::println("{:x}", h.m_length); // prints 12345600
}
// fix: i < 4 (tag is not a C string)