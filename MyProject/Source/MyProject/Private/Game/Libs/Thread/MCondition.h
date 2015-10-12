#ifndef __MCONDITION_H
#define __MCONDITION_H

#include <string>

class MMutex;
class MEvent;

/**
 * @brief 单一对象同步
 */
class MCondition
{
protected:
	MMutex* m_pMMutex;
    MEvent* m_pMEvent;
    bool m_canEnterWait;  // 是否可以进入等待

public:
	MCondition(std::string name = "");
	~MCondition();

	bool getCanEnterWait();
	void wait();
	void notifyAll();
};

#endif