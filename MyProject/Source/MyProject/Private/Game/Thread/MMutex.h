#ifndef __MMUTEX_H
#define __MMUTEX_H

#include "MyProject.h"

/**
    * @brief 互斥
    */
class MMutex
{
private:
	FCriticalSection m_mutex;

public:
	MMutex();
	~MMutex();

	void Lock();
	void Unlock();
};

#endif