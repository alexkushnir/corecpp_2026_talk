#include "Session.h"

Session::Session(int id) : m_id(id) {}

int Session::Id() const
{
    return m_id;
}