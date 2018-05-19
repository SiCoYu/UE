#ifndef __MsgRouteBase_H
#define __MsgRouteBase_H

enum class MsgRouteType
{
	eMRT_BASIC,      // 基本类型
};

enum class MsgRouteId
{
	eMRID_SocketOpened,      // socket Opened
	eMRID_SocketClosed,      // socket Opened
	eMRID_LoadedWebRes,      // web 资源加载完成
	eMRID_ThreadLog,			// 线程打日志
};

#include "IRecycle.h"
#include "IDispatchObject.h"

class MsgRouteBase : public IRecycle, public IDispatchObject
{
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

#endif