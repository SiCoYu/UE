#ifndef __MsgRouteNotify_H
#define __MsgRouteNotify_H

#include "MList.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MsgRouteDispatchHandle;
class MsgRouteBase;

class MsgRouteNotify : public GObject
{
protected:
	MList<MsgRouteDispatchHandle*> mDispatchList;

public:
	void addOneNotify(MsgRouteDispatchHandle* disp);
	void removeOneNotify(MsgRouteDispatchHandle* disp);
	void handleMsg(MsgRouteBase* msg);
};

MY_END_NAMESPACE

#endif