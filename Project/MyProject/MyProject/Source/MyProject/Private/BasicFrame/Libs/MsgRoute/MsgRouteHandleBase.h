#ifndef __MsgRouteHandleBase_H
#define __MsgRouteHandleBase_H

#include <map>
#include "MsgRouteDelegate.h"

class MsgRouteBase;

class MsgRouteHandleBase
{
public:
	std::map<int, MsgRouteDelegate> mId2HandleDic;

public:
	MsgRouteHandleBase();
	// warning C4265: 'MsgRouteHandleBase': class has virtual functions, but destructor is not virtual
	virtual ~MsgRouteHandleBase();
	virtual void handleMsg(MsgRouteBase* msg);
};

#endif