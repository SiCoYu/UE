#ifndef __MCondition_H
#define __MCondition_H

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MMutex;
class MEvent;

/**
 * @brief 单一对象同步
 */
class MCondition
{
protected:
	MMutex* mMutex;
    MEvent* mEvent;
    bool mCanEnterWait;  // 是否可以进入等待

public:
	MCondition(std::string name = "");
	~MCondition();

	void init();
	void dispose();

	bool getCanEnterWait();
	void wait();
	void notifyAll();
};

MY_END_NAMESPACE

#endif