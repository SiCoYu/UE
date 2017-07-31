#include "MyProject.h"
#include "MMutex.h"

MMutex::MMutex()
{
#ifdef USE_EXTERN_THREAD
	mMutex = new Mutex();
#else
	mMutex = new FCriticalSection();
#endif
}

MMutex::~MMutex()
{
#ifdef USE_EXTERN_THREAD
	delete mMutex;
#else
	delete mMutex;
#endif
}

#ifdef USE_EXTERN_THREAD
Mutex* MMutex::getMutex()
#else
FCriticalSection* MMutex::getMutex()
#endif
{
	return mMutex;
}

void MMutex::Lock()
{
#ifdef USE_EXTERN_THREAD
	mMutex->Lock();
#else
	mMutex->Lock();
#endif
}

void MMutex::Unlock()
{
#ifdef USE_EXTERN_THREAD
	mMutex->Lock();
#else
	mMutex->Unlock();
#endif
}