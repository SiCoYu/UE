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
	MCircularBuffer* m_circularBuffer;    // ���λ�����

	ByteBuffer* m_headerBA;     // ��Ҫ����������ͷ�Ĵ�С
	ByteBuffer* m_msgBodyBA;        // ���ص��ֽ�����

protected:
	/**
	* @brief ��� CB ���Ƿ���һ����������Ϣ
	*/
	bool checkHasMsg();

public:
	MsgBuffer(uint32 initCapacity = BufferCV.INIT_CAPACITY, uint32 maxCapacity = BufferCV.MAX_CAPACITY);
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