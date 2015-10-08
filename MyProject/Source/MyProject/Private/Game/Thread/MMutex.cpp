#include "MyProject.h"
#include "MMutex.h"

MMutex::MMutex()
{
#ifdef USE_EXTERN_THREAD
	m_pMutex = new Mutex();
#else
	m_pMutex = new FCriticalSection();
#endif
}

MMutex::~MMutex()
{
#ifdef USE_EXTERN_THREAD
	delete m_pMutex;
#else
	delete m_pMutex;
#endif
}

void MMutex::Lock()
{
#ifdef USE_EXTERN_THREAD
	m_pMutex->Lock();
#else
	m_pMutex->Lock();
#endif
}

void MMutex::Unlock()
{
#ifdef USE_EXTERN_THREAD
	m_pMutex->Lock();
#else
	m_pMutex->Unlock();
#endif
}