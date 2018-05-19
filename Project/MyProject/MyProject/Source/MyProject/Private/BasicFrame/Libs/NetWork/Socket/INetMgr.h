#ifndef __INETMGR_H
#define __INETMGR_H

#include "MyProject.h"
#include <string>

class MByteBuffer;

class INetMgr
{
public:
	virtual ~INetMgr(){};
	virtual void init() = 0;
	virtual void dispose() = 0;
	virtual void openSocket(std::string ip, uint32 port) = 0;
	virtual void recAndSendMsg() = 0;
	virtual MByteBuffer* getSendBA() = 0;
	virtual void send(bool bnet = true) = 0;
};

#endif		// __INETMGR_H