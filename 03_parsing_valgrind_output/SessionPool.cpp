#include "SessionPool.h"
 
Session* SessionPool::acquire(int id) {
    return new Session(id);
}
 
void SessionPool::release(Session* s) {
    delete s;
}
 