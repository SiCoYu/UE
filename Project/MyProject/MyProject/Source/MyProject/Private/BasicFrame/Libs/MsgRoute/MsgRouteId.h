#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MsgRouteId
{
	eMRID_SocketOpened,      // socket Opened
	eMRID_SocketClosed,      // socket Opened
	eMRID_LoadedWebRes,      // web ��Դ�������
	eMRID_ThreadLog,			// �̴߳���־
};

MY_END_NAMESPACE