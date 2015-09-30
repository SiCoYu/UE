#include "MLock.h"

MLock::MLock(MMutex* mutex)
	: m_Lock(mutex)
{
    
}

void MLock::~MLock()
{
    
}