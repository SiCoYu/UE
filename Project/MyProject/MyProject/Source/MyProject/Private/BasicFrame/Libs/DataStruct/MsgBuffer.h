#ifndef __MSGBUFFER_H
#define __MSGBUFFER_H

#include "BufferCV.h"

class MCircularBuffer;
class ByteBuffer;

/**
 * @brief ��Ϣ������
 */
class MsgBuffer
{
	friend class ClientBuffer;

protected:
	MCircularBuffer* mCircularBuffer;    // ���λ�����

	ByteBuffer* mHeaderBA;     // ��Ҫ����������ͷ�Ĵ�С
	ByteBuffer* mMsgBodyBA;        // ���ص��ֽ�����

protected:
	/**
	* @brief ��� CB ���Ƿ���һ����������Ϣ
	*/
	bool checkHasMsg();

public:
	MsgBuffer(uint32 initCapacity = BufferCV::INIT_CAPACITY, uint32 maxCapacity = BufferCV::MAX_CAPACITY);
	~MsgBuffer();

	ByteBuffer* getHeaderBA();
	ByteBuffer* getMsgBodyBA();
	MCircularBuffer* getCircularBuffer();

	/**
	* @brief ��ȡǰ��ĵ�һ����������Ϣ���ݿ�
	*/
	bool popFront();
};

#endif				// __MSGBUFFER_H