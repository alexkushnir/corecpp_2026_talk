#pragma once

#include "Session.h"
 
class SessionPool {
public:
    Session* acquire(int id);
    void release(Session* s);
};