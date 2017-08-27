#ifndef __MsgRouteDispHandle_H
#define __MsgRouteDispHandle_H

#include <map>

class MsgRouteHandleBase;
class MsgRouteBase;

class MsgRouteDispHandle
{
public:
	std::map<int, MsgRouteHandleBase*> mId2DispDic;

public:
	MsgRouteDispHandle();
	virtual ~MsgRouteDispHandle();

	virtual void handleMsg(MsgRouteBase* msg);
};

#endif