#ifndef __NETTHREAD_H
#define __NETTHREAD_H

class NetThread
{
protected:
	bool m_ExitFlag;           // �˳���־

public:
	NetThread();

	/**
	*brief �̻߳ص�����
	*/
	void threadHandle();
};

#endif				// __NETTHREAD_H