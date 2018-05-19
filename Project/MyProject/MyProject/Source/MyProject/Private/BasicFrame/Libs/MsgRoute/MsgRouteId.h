#pragma once

enum class MsgRouteId
{
	eMRID_SocketOpened,      // socket Opened
	eMRID_SocketClosed,      // socket Opened
	eMRID_LoadedWebRes,      // web 资源加载完成
	eMRID_ThreadLog,			// 线程打日志
};