#ifndef __CIRCULARBUFFER_H
#define __CIRCULARBUFFER_H

#include <cstddef>
#include <iostream>
#include <vector>

class MCircularBuffer
{
public:
	MCircularBuffer();
	std::size_t size();
	bool full();
	bool empty();
	void linearize();
	bool isLinearized();
	size_t capacity();
	void setCapacity(size_t newCapacity);
	bool canAddData(uint num);

	void pushBack(char* pItem, std::size_t startPos, std::size_t len);
	bool pushFront(char* pItem, std::size_t startPos, std::size_t len);
	bool popBack(char* pItem, std::size_t startPos, std::size_t len);
	char back(char* pItem, std::size_t startPos, std::size_t len);
	bool popFront(char* pItem, std::size_t startPos, std::size_t len);
	char front(char* pItem, std::size_t startPos, std::size_t len);

protected:
	bool canAddData(uint32 num);

private:
	char* m_storage;
	std::size_t m_head, m_tail, m_size, m_iCapacity;
};


#endif				// __CIRCULARBUFFER_H