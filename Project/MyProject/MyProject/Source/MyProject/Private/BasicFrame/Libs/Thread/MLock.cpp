#include "MyProject.h"
#include "MLock.h"
#include "MMutex.h"

MLock::MLock(MMutex* mutex)
	: mLock(mutex->getMutex())
{
    
}

MLock::~MLock()
{
    
}