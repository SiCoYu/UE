#include "MyProject.h"
#include "MList.h"

template <class T>
MList<T>::MList()
{
	
}

template <class T>
MList<T>::MList(int capacity)
	: m_list(capacity)
{
	
}

template <class T>
MList<T>::~MList()
{

}

template <class T>
std::vector<T> MList<T>::getList()
{
	return m_list;
}

template <class T>
int MList<T>::getUniqueId()
{
	return m_uniqueId;
}

template <class T>
void MList<T>::setUniqueId(int value)
{
	m_uniqueId = value;
}

template <class T>
void MList<T>::Add(T item)
{
	m_list.Add(item);
}

template <class T>
bool MList<T>::Remove(T item)
{
	return m_list.Remove(item);
}

template <class T>
T& operator [] (int index)
{
	return m_list[index];
}

template <class T>
void MList<T>::Clear()
{
	m_list.clear();
}

template <class T>
int MList<T>::Count()
{
	return m_list.size();
}

template <class T>
void MList<T>::RemoveAt(int index)
{
	UtilVector::RemoveAt(m_list, index);
}

template <class T>
int MList<T>::IndexOf(T item)
{
	return UtilVector::IndexOf(m_list, item);
}

template <class T>
void MList<T>::Insert(int index, T item)
{
	if (index <= Count())
	{
		UtilVector::Insert(m_list, index, item);
	}
	else
	{
		g_pLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, Count()));
	}
}

template <class T>
bool MList<T>::Contains(T item)
{
	return IndexOf(item) != -1;
}