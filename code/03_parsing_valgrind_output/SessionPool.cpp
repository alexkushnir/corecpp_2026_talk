#include "SessionPool.h"

Session* SessionPool::Acquire(int id)
{
    return new Session(id);
}

void SessionPool::Release(Session* s)
{
    delete s;
}
