#ifndef __NetDispHandle_H
#define __NetDispHandle_H

#include <vector>

class NetDispHandle;
class ByteBuffer;

class NetDispList
{
protected:
    int m_revMsgCnt;      // 接收到消息的数量
    int m_handleMsgCnt;   // 处理的消息的数量

    std::vector<NetDispHandle*> m_netDispList;
    bool m_bStopNetHandle;       // 是否停止网络消息处理

public:
	NetDispList();

	bool getBStopNetHandle();
	void setBStopNetHandle(bool value);

	void addOneDisp(NetDispHandle* disp);
	void removeOneDisp(NetDispHandle* disp);
	void handleMsg(ByteBuffer* msg);
	void addOneRevMsg();

	void addOneHandleMsg();
	void clearOneRevMsg();
	void clearOneHandleMsg();
};

#endif