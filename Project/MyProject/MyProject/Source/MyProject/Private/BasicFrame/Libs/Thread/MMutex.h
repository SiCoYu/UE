#ifndef __MMutex_H
#define __MMutex_H

//#include "MyProject.h"
#include "PlatformDefine.h"
//#include "GObject.h"

// 如果使用外部线程
//#ifdef USE_EXTERN_THREAD
//	#include "Windows/AllowWindowsPlatformTypes.h"
//
//	#include "Sockets/Mutex.h"
//
//	#include "Windows/HideWindowsPlatformTypes.h"
//#endif

// error C2371: 'FCriticalSection': redefinition; different basic types
// typedef FWindowsCriticalSection FCriticalSection;
// Engine\Source\Runtime\Core\Public\Windows\WindowsCriticalSection.h
//class FCriticalSection;

/**
 * @brief 互斥
 */
//class MMutex : public GObject
class MMutex
{
private:
//#ifdef USE_EXTERN_THREAD
//	Mutex* mMutex;
//#else
	FCriticalSection* mMutex;
//#endif

public:
	MMutex();
	~MMutex();

//#ifdef USE_EXTERN_THREAD
//	Mutex* getMutex();
//#else
	FCriticalSection* getMutex();
//#endif

	void Lock();
	void Unlock();
};

#endif