// Produces each of Memcheck's four leak kinds (slide "Not All Leaks Are Equal").
//
//   valgrind --leak-check=full --show-leak-kinds=all ./leak_kinds

#include <cstdlib>
#include <cstring>

struct Node
{
    Node* m_child = nullptr;
    char m_payload[24] = {};
};

// Pointers that are still alive when main() returns.
char* gConfig = nullptr; // points to the START of a block
char* gCursor = nullptr; // points into the MIDDLE of a block

// 1. definitely lost: the only pointer to the block goes away.
void DefinitelyLost()
{
    int* samples = new int[16];
    samples[0] = 1;
} // 'samples' goes out of scope; nothing points to the block anymore

// 2. indirectly lost: 'child' is only reachable through 'root',
//    and 'root' itself is lost.
void IndirectlyLost()
{
    Node* root = new Node;
    root->m_child = new Node;
} // root: definitely lost (32 bytes), child: indirectly lost (32 bytes)

// 3. possibly lost: only an interior pointer survives.
void PossiblyLost()
{
    char* buffer = static_cast<char*>(std::malloc(64));
    std::memset(buffer, 0, 64);
    gCursor = buffer + 16; // no pointer to the start is kept
}

// 4. still reachable: a global still points at the block at exit.
void StillReachable()
{
    gConfig = static_cast<char*>(std::malloc(128));
    std::strcpy(gConfig, "log_level=debug");
}

int main()
{
    DefinitelyLost();
    IndirectlyLost();
    PossiblyLost();
    StillReachable();
    return 0;
}