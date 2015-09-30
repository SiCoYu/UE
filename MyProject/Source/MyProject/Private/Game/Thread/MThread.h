#ifndef __MTHREAD_H
#define __MTHREAD_H

#include "MyProject.h"
#include <string>

class MEvent;

/**
    *@brief 基本的线程
    */
class MThread : public FRunnable
{
protected:
	bool m_ExitFlag;           // 退出标志
	FRunnableThread* m_pThread;
	std::string m_threadName;
	MEvent* m_pSyncEvent;

public:
	MThread();
	~MThread();

	void setExitFlag(bool value);
    // 函数区域
    /**
     *@brief 开启一个线程
     */
	void start();
	void join();

	virtual bool Init(void) override;
	virtual void Exit(void) override;
	virtual uint32 Run(void) override;
};

#endif