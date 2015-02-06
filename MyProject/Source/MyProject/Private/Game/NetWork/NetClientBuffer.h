#ifndef __NETCLIENTBUFFER_H
#define __NETCLIENTBUFFER_H

/**
* @brief 消息缓冲区
*/
class NetClientBuffer
{
protected:
	MsgBuffer* m_recvRawBuffer;     // 直接从服务器接收到的原始的数据，可能压缩和加密过
	MsgBuffer* m_recvMsgBuffer;		// 解压解密后可以使用的缓冲区
	MsgBuffer* m_sendRawBuffer;		// 发送临时缓冲区，发送的数据都暂时放在这里
	MsgBuffer* m_sendMsgBuffer;		// 发送缓冲区，压缩或者加密过的

	MCircularBuffer* m_dynBuff;        // 接收到的临时数据，将要放到 m_recvRawBuffer 中去
	ByteBuffer* m_unCompressHeaderBA;  // 存放解压后的头的长度
	ByteBuffer* m_sendData;            // 存放将要发送的数据，将要放到 m_sendBuffer 中去
	ByteBuffer* m_tmpData;             // 临时需要转换的数据放在这里

public:
	NetClientBuffer();
	~NetClientBuffer();
};

#endif				// __NETCLIENTBUFFER_H