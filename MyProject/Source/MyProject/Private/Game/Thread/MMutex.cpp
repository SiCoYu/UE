#include "MMutex.h"

MMutex::MMutex()
{
    
}

MMutex::~MMutex()
{

}

void MMutex::Lock()
{
    m_mutex.Lock();
}

void MMutex::Unlock()
{
	m_mutex.Unlock();
}