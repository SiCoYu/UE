#ifndef __CIRCULARBUFFER_H
#define __CIRCULARBUFFER_H

#include <cstddef>
#include <iostream>
#include <vector>
#include "BufferDefaultValue.h"

class MCircularBuffer
{
private:
	char* m_storage;
	std::size_t m_head;
	std::size_t m_tail;
	std::size_t m_size;
	std::size_t m_iCapacity;
	std::size_t m_maxCapacity;

protected:
	bool canAddData(uint32 num);

public:
	MCircularBuffer(size_t initCapacity = INITCAPACITY, size_t maxCapacity = MAXCAPACITY);
	~MCircularBuffer();

public:
	std::size_t size();
	bool full();
	bool empty();
	void linearize();
	bool isLinearized();
	size_t capacity();
	void setCapacity(size_t newCapacity);
	size_t maxCapacity();
	void clear();
	char* getStorage();

	// 添加和获取数据
	void pushBack(char* pItem, std::size_t startPos, std::size_t len);
	void pushFront(char* pItem, std::size_t startPos, std::size_t len);
	bool popBack(char* pItem, std::size_t startPos, std::size_t len);
	bool back(char* pItem, std::size_t startPos, std::size_t len);
	bool popFront(char* pItem, std::size_t startPos, std::size_t len);
	bool front(char* pItem, std::size_t startPos, std::size_t len);
	void popBackLenNoData(std::size_t len);
	void popFrontLenNoData(std::size_t len);
};


#endif				// __CIRCULARBUFFER_H