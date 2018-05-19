#ifndef __MsgRouteNotify_H
#define __MsgRouteNotify_H

#include "MList.h"

class MsgRouteDispatchHandle;
class MsgRouteBase;

class MsgRouteNotify
{
protected:
	MList<MsgRouteDispatchHandle*> mDispatchList;

public:
	void addOneNotify(MsgRouteDispatchHandle* disp);
	void removeOneNotify(MsgRouteDispatchHandle* disp);
	void handleMsg(MsgRouteBase* msg);
};

#endif