#ifndef __MLOCK_H
#define __MLOCK_H

#include "MyProject.h"
#include "GObject.h"

class MMutex;

/**
 * @brief 锁操作
 */
class MLock : public GObject
{
protected:
	FScopeLock mLock;

public:
	MLock(MMutex* mutex);
	~MLock();
};

#endif