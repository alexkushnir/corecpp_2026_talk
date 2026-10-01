// ASan demo: a session keeps a stale pointer to a pooled block after
// Close(). The pool never gives memory back to the heap, so without
// poisoning the stale read just returns the old value and the test passes,
// even under ASan. With the poison/unpoison macros in pool.cpp, ASan
// reports use-after-poison.
#include <gtest/gtest.h>

#include "Session.h"

TEST(Session, ReportsSizeAfterClose)
{
    Pool pool(16);
    Session session(pool);
    session.Receive("hello");
    session.Close();
    EXPECT_EQ(session.LastSize(), 5u); // stale read: passes without poisoning
}