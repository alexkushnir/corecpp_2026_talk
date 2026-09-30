#pragma once

#include "SessionPool.h"
 
struct Request {
  Session* session;
};
 
void close_idle(SessionPool& pool, Request& req);
int handle(Request& req);