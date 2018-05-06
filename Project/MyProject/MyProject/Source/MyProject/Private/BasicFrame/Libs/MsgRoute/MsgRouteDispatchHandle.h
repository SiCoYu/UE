#ifndef __MsgRouteDispatchHandle_H
#define __MsgRouteDispatchHandle_H

#include <map>

class MsgRouteHandleBase;
class MsgRouteBase;

class MsgRouteDispatchHandle
{
public:
	std::map<int, MsgRouteHandleBase*> mId2DispDic;

public:
	MsgRouteDispatchHandle();
	virtual ~MsgRouteDispatchHandle();

	virtual void handleMsg(MsgRouteBase* msg);
};

#endif