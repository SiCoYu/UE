#ifndef __MLock_H
#define __MLock_H

#include "MyProject.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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

	void init();
	void dispose();
};

MY_END_NAMESPACE

#endif