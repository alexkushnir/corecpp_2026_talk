#include "Server.h"

void close_idle(SessionPool& pool, Request& req)
{
    pool.release(req.session); // BUG: req.session still points at it
}

int handle(Request& req)
{
    return req.session->id(); // reads a freed Session
}