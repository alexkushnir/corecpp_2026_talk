#include "Session.h"
 
Session::Session(int id) 
    : m_id(id) 
{}
 
int Session::id() const {
    return m_id;
}