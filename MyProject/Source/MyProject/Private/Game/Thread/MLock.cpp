#include "MyProject.h"
#include "MLock.h"
#include "MMutex.h"

MLock::MLock(MMutex* mutex)
	: m_Lock(mutex->getMutex())
{
    
}

MLock::~MLock()
{
    
}