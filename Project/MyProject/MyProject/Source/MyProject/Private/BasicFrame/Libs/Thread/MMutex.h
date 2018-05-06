#ifndef __MMutex_H
#define __MMutex_H

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
	Mutex* mMutex;
#else
	FCriticalSection* mMutex;
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