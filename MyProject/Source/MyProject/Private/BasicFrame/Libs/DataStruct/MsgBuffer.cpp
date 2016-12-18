#include "MyProject.h"
#include "MsgBuffer.h"
#include "MCircularBuffer.h"
#include "ByteBuffer.h"
#include "MsgCV.h"

MsgBuffer::MsgBuffer(uint32 initCapacity, uint32 maxCapacity)
{
	mCircularBuffer = new MCircularBuffer(initCapacity, maxCapacity);
	mHeaderBA = new ByteBuffer();
	mMsgBodyBA = new ByteBuffer();
}

MsgBuffer::~MsgBuffer()
{
	delete mCircularBuffer;
	delete mHeaderBA;
	delete mMsgBodyBA;
}

ByteBuffer* MsgBuffer::getHeaderBA()
{
	return mHeaderBA;
}

ByteBuffer* MsgBuffer::getMsgBodyBA()
{
	return mMsgBodyBA;
}

MCircularBuffer* MsgBuffer::getCircularBuffer()
{
	return mCircularBuffer;
}

bool MsgBuffer::checkHasMsg()
{
	mCircularBuffer->frontBA(mHeaderBA, MsgCV::HEADER_SIZE);  // �����ݶ�ȡ�� mHeaderBA
	uint32 msglen = 0;
	mHeaderBA->readUnsignedInt32(msglen);
#if MSG_COMPRESS
	if ((msglen & MsgCV::PACKET_ZIP) > 0)         // �����ѹ����־
	{
		msglen &= (~MsgCV::PACKET_ZIP);         // ȥ��ѹ����־λ
	}
#endif
	if (msglen <= mCircularBuffer->getSize() - MsgCV::HEADER_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief ��ȡǰ��ĵ�һ����������Ϣ���ݿ�
*/
bool MsgBuffer::popFront()
{
	bool ret = false;
	if (mCircularBuffer->getSize() > MsgCV::HEADER_SIZE)         // ����Ҫ�� DataCV.HEADER_SIZE ��С�� 1 ����������� DataCV.HEADER_SIZE ����ֻ��˵��ֻ�д�С�ֶΣ�û������
	{
		mCircularBuffer->frontBA(mHeaderBA, MsgCV::HEADER_SIZE);  // �������������Ϣ�ĳ��ȣ����ǲ���ȥ����Ϣͷ��
		uint32 msglen = 0;
		mHeaderBA->readUnsignedInt32(msglen);
#if MSG_COMPRESS
		if ((msglen & MsgCV.PACKET_ZIP) > 0)         // �����ѹ����־
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // ȥ��ѹ����־λ
		}
#endif

		if (msglen <= mCircularBuffer->getSize() - MsgCV::HEADER_SIZE)
		{
			mCircularBuffer->popFrontLen(MsgCV::HEADER_SIZE);
			mCircularBuffer->popFrontBA(mMsgBodyBA, msglen);
			ret = true;
		}
	}

	if (mCircularBuffer->empty())     // ����Ѿ���գ���ֱ������
	{
		mCircularBuffer->clear();    // ��дָ���ͷ��ʼ����ʽд����Ҫд��������
	}

	return ret;
}