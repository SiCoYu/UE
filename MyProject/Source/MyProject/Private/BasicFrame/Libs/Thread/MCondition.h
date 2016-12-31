#ifndef __MCondition_H
#define __MCondition_H

#include <string>

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

	bool getCanEnterWait();
	void wait();
	void notifyAll();
};

#endif