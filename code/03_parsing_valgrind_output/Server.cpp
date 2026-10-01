#include "Server.h"

void CloseIdle(SessionPool& pool, Request& req)
{
    pool.Release(req.m_session); // BUG: req.session still points at it
}

int Handle(Request& req)
{
    return req.session->id(); // reads a freed Session
}