#include <cstdint>
#include <print>

struct Header {
    char tag[4];
    std::uint32_t length;
};
 
void SetTag(Header& h, const char* tag) {
    for (int i = 0; i <= 4; ++i) {  // copies the '\0' too
        h.tag[i] = tag[i];
    }
}

int main() {
    Header h{{}, 0x12345678};
    SetTag(h, "DATA");
    std::println("{:x}", h.length);  // prints 12345600
}
// fix: i < 4 (tag is not a C string)