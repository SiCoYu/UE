#ifndef __MMsgBuffer_H
#define __MMsgBuffer_H

#include "BufferCV.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MCircularBuffer;
class MByteBuffer;

/**
 * @brief ��Ϣ������
 */
class MMsgBuffer
{
	friend class MClientBuffer;

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
	MMsgBuffer(
		uint32 initCapacity = BufferCV::eINIT_CAPACITY, 
		uint32 maxCapacity = BufferCV::eMAX_CAPACITY
	);
	~MMsgBuffer();

	MByteBuffer* getHeaderBA();
	MByteBuffer* getMsgBodyBA();
	MCircularBuffer* getCircularBuffer();

	/**
	* @brief ��ȡǰ��ĵ�һ����������Ϣ���ݿ�
	*/
	bool popFront();
};

MY_END_NAMESPACE

#endif				// __MMsgBuffer_H