#ifndef __NETTHREAD_H
#define __NETTHREAD_H

class NetThread
{
protected:
	bool m_ExitFlag;           // 退出标志

public:
	NetThread();

	/**
	*brief 线程回调函数
	*/
	void threadHandle();
};

#endif				// __NETTHREAD_H