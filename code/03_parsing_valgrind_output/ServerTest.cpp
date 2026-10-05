// Memcheck demo: a session is released while a request still holds a
// pointer to it. The test passes; Valgrind reports an invalid read
// inside a freed 64-byte block, with the release() stack.
#include <gtest/gtest.h>

#include "Server.h"

TEST(Server, HandlesRequestAfterIdleCheck)
{
    SessionPool pool;
    Request req{pool.Acquire(42)};
    CloseIdle(pool, req);
    EXPECT_EQ(Handle(req), 42); // passes: freed block still holds 42
}