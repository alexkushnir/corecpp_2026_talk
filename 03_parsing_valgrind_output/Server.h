#pragma once

#include "SessionPool.h"

struct Request
{
    Session* m_session;
};

void CloseIdle(SessionPool& pool, Request& req);
int Handle(Request& req);