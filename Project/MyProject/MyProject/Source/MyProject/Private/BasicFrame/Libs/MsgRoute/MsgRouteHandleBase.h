#ifndef __MsgRouteHandleBase_H
#define __MsgRouteHandleBase_H

#include "MDcitionary.h"
#include "MsgRouteDelegate.h"

class MsgRouteBase;

class MsgRouteHandleBase
{
public:
	MDcitionary<int, MsgRouteDelegate> mId2HandleDic;

public:
	MsgRouteHandleBase();
	// warning C4265: 'MsgRouteHandleBase': class has virtual functions, but destructor is not virtual
	virtual ~MsgRouteHandleBase();
	virtual void handleMsg(MsgRouteBase* msg);
};

#endif