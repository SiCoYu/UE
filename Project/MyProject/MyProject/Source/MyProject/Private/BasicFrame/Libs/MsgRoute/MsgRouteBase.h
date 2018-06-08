#ifndef __MsgRouteBase_H
#define __MsgRouteBase_H

#include "IPoolObject.h"
#include "IDispatchObject.h"
#include "MsgRouteType.h"
#include "MsgRouteId.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MsgRouteBase : public GObject, public IPoolObject, public IDispatchObject
{
	M_DECLARE_CLASS(MsgRouteBase, GObject)

public:
	MsgRouteType mMsgType;
    MsgRouteId mMsgId;          // 只需要一个 Id 就行了

public:
	MsgRouteBase();
	MsgRouteBase(MsgRouteId id);
	// warning C4265: 'MsgRouteBase': class has virtual functions, but destructor is not virtual
	virtual ~MsgRouteBase();
	virtual void resetDefault();
};

MY_END_NAMESPACE

#endif