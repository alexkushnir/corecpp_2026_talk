#include <cstring>

struct Header { int len; int flags; };
int parse(const char* buf) {
  Header h;                // not zeroed
  std::memcpy(&h.len, buf, 4);
  if (h.flags & 0x1)       // uninit!
    return -1;
  return h.len;
}

int main()
{
    char buf[] = { 0x01, 0x02, 0x03, 0x04 };
    parse(buf);

    return 0;
}