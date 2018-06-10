#include "MyProject.h"
#include "MLock.h"
#include "MMutex.h"

MY_BEGIN_NAMESPACE(MyNS)

MLock::MLock(MMutex* mutex)
	: mLock(mutex->getMutex())
{
    
}

MLock::~MLock()
{
    
}

void MLock::init()
{

}

void MLock::dispose()
{

}

MY_END_NAMESPACE