#pragma once

#include "Session.h"

class SessionPool
{
public:
    Session* Acquire(int id);
    void Release(Session* s);
};