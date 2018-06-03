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
 *@brief 浪费一个自己，这样判断也好判断，并且索引也不用减 1 ，因此浪费一个字节
 */
class MCircularBuffer : public GObject
{
protected:
	MDynBuffer<char>* mDynBuffer;
	uint32 mFirst;             // 当前缓冲区数据的第一个索引
	uint32 mLast;              // 当前缓冲区数据的最后一个索引的后面一个索引，浪费一个字节
	MByteBuffer* mTmpBA;        // 临时数据

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

	// 添加和获取数据
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