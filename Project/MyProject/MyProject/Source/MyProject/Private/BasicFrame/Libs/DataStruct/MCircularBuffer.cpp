#include "MyProject.h"
#include "MCircularBuffer.h"
#include "DynBufResizePolicy.h"
#include "Array.h"
#include "ByteBuffer.h"

/**
 * @brief ���캯��
 */
MCircularBuffer::MCircularBuffer(size_t initCapacity, size_t maxCapacity)
{
	mDynBuffer = new DynBuffer<char>(initCapacity, maxCapacity);

	mFirst = 0;
	mLast = 0;

	mTmpBA = new ByteBuffer();
}

MCircularBuffer::~MCircularBuffer()
{
	delete mDynBuffer;
	delete mTmpBA;
}

uint32 MCircularBuffer::getFirst()
{
	return mFirst;
}

uint32 MCircularBuffer::getLast()
{
	return mLast;
}

char* MCircularBuffer::getBuffer()
{
	return mDynBuffer->mBuffer;
}

std::size_t MCircularBuffer::getSize()
{
	return mDynBuffer->mSize;
}

void MCircularBuffer::setSize(std::size_t value)
{
	mDynBuffer->setSize(value);
}

bool MCircularBuffer::isLinearized()
{
	if (this->getSize() == 0)
	{
		return true;
	}

	return mFirst < mLast;
}

bool MCircularBuffer::empty()
{
	return mDynBuffer->mSize == 0;
}

size_t MCircularBuffer::getCapacity()
{
	return mDynBuffer->mCapacity;
}

bool MCircularBuffer::full()
{
	return this->getCapacity() == this->getSize();
}

void MCircularBuffer::clear()
{
	mDynBuffer->mSize = 0;
	mFirst = 0;
	mLast = 0;
}

void MCircularBuffer::linearize()
{
	if (this->empty())        // û������
	{
		return;
	}
	if (isLinearized())
	{
		return;
	}
	else
	{
		// �������������������ڴ�ռ���
		char* tmp = new char[mLast];
		Array::Copy(mDynBuffer->mBuffer, 0, tmp, 0, mLast);  // ����һ���ڴ�ռ��е����ݵ� tmp
		Array::Copy(mDynBuffer->mBuffer, mFirst, mDynBuffer->mBuffer, 0, mDynBuffer->mCapacity - mFirst);  // ������һ�����ݵ� 0 ����λ��
		Array::Copy(tmp, 0, mDynBuffer->mBuffer, mDynBuffer->mCapacity - mFirst, mLast);      // �����ڶ������ݵ�������

		delete tmp;

		mFirst = 0;
		mLast = this->getSize();
	}
}

void MCircularBuffer::setCapacity(std::size_t newCapacity)
{
	if (newCapacity == this->getCapacity())
	{
		return;
	}
	if (newCapacity < this->getSize())       // ���ܷ���ȵ�ǰ�Ѿ�ռ�еĿռ仹С�Ŀռ�
	{
		return;
	}
	char* tmpbuff = new char[newCapacity];   // �����µĿռ�
	if (isLinearized()) // �������һ���ڴ�ռ�
	{
		// �Ѿ������Կռ�����Ȼ�������ƶ������� 0 ��λ��
		Array::Copy(mDynBuffer->mBuffer, mFirst, tmpbuff, 0, mDynBuffer->mSize);
	}
	else    // ����������ڴ�ռ�
	{
		Array::Copy(mDynBuffer->mBuffer, mFirst, tmpbuff, 0, mDynBuffer->mCapacity - mFirst);
		Array::Copy(mDynBuffer->mBuffer, 0, tmpbuff, mDynBuffer->mCapacity - mFirst, mLast);
	}

	mFirst = 0;
	mLast = mDynBuffer->mSize;
	mDynBuffer->mCapacity = newCapacity;
	delete mDynBuffer->mBuffer;
	mDynBuffer->mBuffer = tmpbuff;
}

/**
*@brief �ܷ���� num ���ȵ�����
*/
bool MCircularBuffer::canAddData(uint32 num)
{
	if (mDynBuffer->mCapacity - mDynBuffer->mSize > num) // �˷�һ���ֽڣ����� >= ��ʹ�� > 
	{
		return true;
	}

	return false;
}

/**
*@brief ��洢��β�����һ������
*/
void MCircularBuffer::pushBackArr(char* items, uint32 start, std::size_t len)
{
	if (!canAddData(len)) // �洢�ռ����Ҫ��ʵ���������ٶ� 1
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + mDynBuffer->mSize, mDynBuffer->mCapacity, mDynBuffer->mMaxCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= (mDynBuffer->mCapacity - mLast))
		{
			Array::Copy(items, start, mDynBuffer->mBuffer, mLast, len);
		}
		else
		{
			Array::Copy(items, start, mDynBuffer->mBuffer, mLast, mDynBuffer->mCapacity - mLast);
			Array::Copy(items, mDynBuffer->mCapacity - mLast, mDynBuffer->mBuffer, 0, len - (mDynBuffer->mCapacity - mLast));
		}
	}
	else
	{
		Array::Copy(items, start, mDynBuffer->mBuffer, mLast, len);
	}

	mLast += len;
	mLast %= mDynBuffer->mCapacity;

	mDynBuffer->mSize += len;
}

void MCircularBuffer::pushBackBA(ByteBuffer* bu)
{
	//pushBack(bu.dynBuff.buff, bu.position, bu.bytesAvailable);
	pushBackArr(bu->getDynBuffer()->getBuffer(), 0, bu->getLength());
}

/**
*@brief ��洢��ͷ�����һ������
*/
void MCircularBuffer::pushFrontArr(char* items, std::size_t len)
{
	if (!canAddData(len)) // �洢�ռ����Ҫ��ʵ���������ٶ� 1
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + mDynBuffer->mSize, mDynBuffer->mCapacity, mDynBuffer->mMaxCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= mFirst)
		{
			Array::Copy(items, 0, mDynBuffer->mBuffer, mFirst - len, len);
		}
		else
		{
			Array::Copy(items, len - mFirst, mDynBuffer->mBuffer, 0, mFirst);
			Array::Copy(items, 0, mDynBuffer->mBuffer, mDynBuffer->mCapacity - (len - mFirst), len - mFirst);
		}
	}
	else
	{
		Array::Copy(items, 0, mDynBuffer->mBuffer, mFirst - len, len);
	}

	if (len <= mFirst)
	{
		mFirst -= len;
	}
	else
	{
		mFirst = mDynBuffer->mCapacity - (len - mFirst);
	}
	mDynBuffer->mSize += len;
}

/**
* @brief �� CB �ж�ȡ���ݣ����ҽ�����ɾ��
*/
void MCircularBuffer::popFrontBA(ByteBuffer* bytearray, std::size_t len)
{
	frontBA(bytearray, len);
	popFrontLen(len);
}

// �����ǻ�ȡ���ݣ�����ɾ��
void MCircularBuffer::frontBA(ByteBuffer* bytearray, std::size_t len)
{
	bytearray->clear();          // ��������Ϊ��ʼֵ
	if (mDynBuffer->mSize >= len)          // ͷ��ռ�� 4 ���ֽ�
	{
		if (isLinearized())      // ��һ���������ڴ�
		{
			bytearray->writeBytes(mDynBuffer->mBuffer, mFirst, len);
		}
		else if (mDynBuffer->mCapacity - mFirst >= len)
		{
			bytearray->writeBytes(mDynBuffer->mBuffer, mFirst, len);
		}
		else
		{
			bytearray->writeBytes(mDynBuffer->mBuffer, mFirst, mDynBuffer->mCapacity - mFirst);
			bytearray->writeBytes(mDynBuffer->mBuffer, 0, len - (mDynBuffer->mCapacity - mFirst));
		}
	}

	bytearray->setPos(0);        // �������ݶ�ȡ��ʼλ��
}

/**
* @brief �� CB ͷ��ɾ������
*/
void MCircularBuffer::popFrontLen(uint32 len)
{
	if (isLinearized())  // ��һ���������ڴ�
	{
		mFirst += len;
	}
	else if (mDynBuffer->mCapacity - mFirst >= len)
	{
		mFirst += len;
	}
	else
	{
		mFirst = len - (mDynBuffer->mCapacity - mFirst);
	}

	mDynBuffer->mSize -= len;
}

// ���Լ�β�����һ�� CirculeBuffer 
void MCircularBuffer::pushBackCB(MCircularBuffer* rhv)
{
	if (mDynBuffer->mCapacity - mDynBuffer->mSize < rhv->getSize())
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(rhv->getSize() + mDynBuffer->mSize, mDynBuffer->mCapacity, mDynBuffer->mMaxCapacity);
		setCapacity(closeSize);
	}
	//this.mSize += rhv.size;
	//this.mLast = this.mSize;

	//mTmpBA.clear();
	rhv->frontBA(mTmpBA, rhv->getSize());
	pushBackBA(mTmpBA);

	//if (rhv.isLinearized()) // �������һ���ڴ�ռ�
	//{
	//    Array.Copy(rhv.buff, rhv.first, mBuffer, 0, rhv.size);
	//}
	//else    // ����������ڴ�ռ�
	//{
	//    Array.Copy(rhv.buff, rhv.first, mBuffer, 0, rhv.capacity() - rhv.first);
	//    Array.Copy(mBuffer, 0, mBuffer, rhv.capacity() - rhv.first, rhv.last);
	//}
	//rhv.clear();
}