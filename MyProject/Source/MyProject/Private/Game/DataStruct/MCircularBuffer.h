#ifndef __CIRCULARBUFFER_H
#define __CIRCULARBUFFER_H

#include "MyProject.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include "BufferDefaultValue.h"

class DynBuffer;
class ByteBuffer;

/**
 *@brief �˷�һ���Լ��������ж�Ҳ���жϣ���������Ҳ���ü� 1 ������˷�һ���ֽ�
 */
class MCircularBuffer
{
protected:
	DynBuffer* m_dynBuffer;
	uint32 m_first;             // ��ǰ���������ݵĵ�һ������
	uint32 m_last;              // ��ǰ���������ݵ����һ�������ĺ���һ���������˷�һ���ֽ�
	ByteBuffer* m_tmpBA;        // ��ʱ����

protected:
	bool canAddData(uint32 num);
	void setCapacity(size_t newCapacity);

public:
	MCircularBuffer(size_t initCapacity = INITCAPACITY, size_t maxCapacity = MAXCAPACITY);
	~MCircularBuffer();

public:
	uint32 getFirst();
	uint32 getLast();
	std::size_t getSize();
	void setSize(std::size_t value);
	char* getBuff();

	bool isLinearized();
	bool empty();
	size_t getCapacity();
	bool full();
	void linearize();
	void clear();

	// ��Ӻͻ�ȡ����
	void pushBackArr(char* items, uint32 start, std::size_t len);
	void pushBackBA(ByteBuffer* bu, std::size_t len);
	void MCircularBuffer::popFrontBA(ByteBuffer* bytearray, std::size_t len);
	void MCircularBuffer::frontBA(ByteBuffer bytearray, std::size_t len);
	void MCircularBuffer::popFrontLen(uint32 len);
	void MCircularBuffer::pushBackCB(MCircularBuffer* rhv);
};


#endif				// __CIRCULARBUFFER_H