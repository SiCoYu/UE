#ifndef __CIRCULARBUFFER_H
#define __CIRCULARBUFFER_H

#include <cstddef>
#include <iostream>

template <typename T, int N>
class MCircularBuffer
{
public:
	//void linearize();
	//bool is_linearized();
	//void rotate();
	//size_t size(){ return m_size; }
	//bool empty(){ return size() == 0; }
	//bool full(){ return capacity() == size(); }
	//size_t reserve(){ return capacity() - size(); }
	//size_t capacity(){ return m_end - m_buff; }
	//void set_capacity(size_t new_capacity);
	//void resize(size_t new_size);
public:
	MCircularBuffer();
	MCircularBuffer(T initial_value);
	std::size_t count();
	bool push(T item);
	void pop();
	T front();
	bool is_full();
	bool is_empty();
private:
	T storage[N + 1];
	std::size_t head, tail;
};

template <typename T, int N>
MCircularBuffer<T, N>::MCircularBuffer() :
head(0),
tail(0)
{
}

template <typename T, int N>
MCircularBuffer<T, N>::MCircularBuffer(T initial_value) :
head(0),
tail(0)
{
	for (int i = 0; i < N; ++i) {
		storage[i] = initial_value;
	}
}

template <typename T, int N>
std::size_t MCircularBuffer<T, N>::count()
{
	if (this->is_full()) {
		return N;
	}
	else {
		return tail - head;
	}
}

template <typename T, int N>
bool MCircularBuffer<T, N>::push(T item)
{
	if (this->is_full()) {
		return false;
	}
	storage[tail++] = item;
	return true;
}

template <typename T, int N>
void MCircularBuffer<T, N>::pop()
{
	if (!this->is_empty()) {
		++head;
	}
}

template <typename T, int N>
T MCircularBuffer<T, N>::front()
{
	return storage[head];
}

template <typename T, int N>
bool MCircularBuffer<T, N>::is_full()
{
	return (tail == N);
}

template <typename T, int N>
bool MCircularBuffer<T, N>::is_empty()
{
	return (head == tail);
}

#endif				// __CIRCULARBUFFER_H