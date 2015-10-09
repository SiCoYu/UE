#ifndef __MMUTEX_H
#define __MMUTEX_H

#include "MyProject.h"
#include "PlatformDefine.h"

// 如果使用外部线程
#ifdef USE_EXTERN_THREAD
	#include "Windows/AllowWindowsPlatformTypes.h"

	#include "Sockets/Mutex.h"

	#include "Windows/HideWindowsPlatformTypes.h"
#endif


/**
    * @brief 互斥
    */
class MMutex
{
private:
#ifdef USE_EXTERN_THREAD
	Mutex* m_pMutex;
#else
	FCriticalSection* m_pMutex;
#endif

public:
	MMutex();
	~MMutex();

#ifdef USE_EXTERN_THREAD
	Mutex* getMutex();
#else
	FCriticalSection* getMutex();
#endif

	void Lock();
	void Unlock();
};

#endif