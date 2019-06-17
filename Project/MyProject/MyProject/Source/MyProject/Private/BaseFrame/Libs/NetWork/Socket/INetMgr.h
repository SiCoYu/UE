#ifndef __INetMgr_H
#define __INetMgr_H

#include "MyProject.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE

#endif		// __INetMgr_H