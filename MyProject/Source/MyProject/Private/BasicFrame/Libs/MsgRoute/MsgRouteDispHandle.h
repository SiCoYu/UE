#ifndef __MsgRouteDispHandle_H
#define __MsgRouteDispHandle_H

#include <map>

class MsgRouteHandleBase;
class MsgRouteBase;

class MsgRouteDispHandle
{
public:
	std::map<int, MsgRouteHandleBase*> m_id2DispDic;

public:
	virtual void handleMsg(MsgRouteBase* msg);
};

#endif