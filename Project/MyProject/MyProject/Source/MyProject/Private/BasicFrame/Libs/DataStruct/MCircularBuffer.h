#ifndef __MCircularBuffer_H
#define __MCircularBuffer_H

#include "Platform.h"
#include <cstddef>
#include <iostream>
#include "BufferCV.h"
#include "MDynBuffer.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

//template <class T> class MDynBuffer<char>;
class MByteBuffer;

/**
 *@brief �˷�һ���Լ��������ж�Ҳ���жϣ���������Ҳ���ü� 1 ������˷�һ���ֽ�
 */
class MCircularBuffer : public GObject
{
protected:
	MDynBuffer<char>* mDynBuffer;
	uint32 mFirst;             // ��ǰ���������ݵĵ�һ������
	uint32 mLast;              // ��ǰ���������ݵ����һ�������ĺ���һ���������˷�һ���ֽ�
	MByteBuffer* mTmpBA;        // ��ʱ����

protected:
	bool canAddData(uint32 num);
	void setCapacity(size_t newCapacity);

public:
	MCircularBuffer(size_t initCapacity = BufferCV::INIT_CAPACITY, size_t maxCapacity = BufferCV::MAX_CAPACITY);
	~MCircularBuffer();

public:
	uint32 getFirst();
	uint32 getLast();
	std::size_t getSize();
	void setSize(std::size_t value);
	char* getBuffer();

	bool isLinearized();
	bool empty();
	size_t getCapacity();
	bool full();
	void linearize();
	void clear();

	// ��Ӻͻ�ȡ����
	void pushBackArr(char* items, uint32 start, std::size_t len);
	void pushBackBA(MByteBuffer* bu);
	void pushFrontArr(char* items, std::size_t len);
	void popFrontBA(MByteBuffer* bytearray, std::size_t len);
	void frontBA(MByteBuffer* bytearray, std::size_t len);
	void popFrontLen(uint32 len);
	void pushBackCB(MCircularBuffer* rhv);
};

MY_END_NAMESPACE

#endif				// __MCircularBuffer_H