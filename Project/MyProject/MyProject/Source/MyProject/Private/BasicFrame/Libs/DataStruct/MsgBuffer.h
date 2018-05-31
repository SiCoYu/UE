#ifndef __MsgBuffer_H
#define __MsgBuffer_H

#include "BufferCV.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MCircularBuffer;
class MByteBuffer;

/**
 * @brief ��Ϣ������
 */
class MsgBuffer
{
	friend class ClientBuffer;

protected:
	MCircularBuffer* mCircularBuffer;    // ���λ�����

	MByteBuffer* mHeaderBA;     // ��Ҫ����������ͷ�Ĵ�С
	MByteBuffer* mMsgBodyBA;        // ���ص��ֽ�����

protected:
	/**
	* @brief ��� CB ���Ƿ���һ����������Ϣ
	*/
	bool checkHasMsg();

public:
	MsgBuffer(uint32 initCapacity = BufferCV::INIT_CAPACITY, uint32 maxCapacity = BufferCV::MAX_CAPACITY);
	~MsgBuffer();

	MByteBuffer* getHeaderBA();
	MByteBuffer* getMsgBodyBA();
	MCircularBuffer* getCircularBuffer();

	/**
	* @brief ��ȡǰ��ĵ�һ����������Ϣ���ݿ�
	*/
	bool popFront();
};

MY_END_NAMESPACE

#endif				// __MsgBuffer_H