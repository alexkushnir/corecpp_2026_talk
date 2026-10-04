#include "Server.h"

void CloseIdle(SessionPool& pool, Request& req)
{
    pool.Release(req.m_session); // BUG: req.m_session still points at it
}

int Handle(Request& req)
{
    return req.m_session->Id(); // reads a freed Session
}