#ifndef __MList_H
	#error "MList.inl file can only include in MList.h"
#endif

#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template <typename T>
MList<T>::MList()
{

}

template <typename T>
MList<T>::MList(int capacity)
	: mList(capacity)
{

}

template <typename T>
MList<T>::~MList()
{

}

template <typename T>
void MList<T>::init()
{

}

template <typename T>
void MList<T>::dispose()
{
	this->clear();
}

template <typename T>
T& MList<T>::get(int index)
{
	return this->mList[index];
}

template <typename T>
void MList<T>::set(int index, T item)
{
	this->mList[index] = item;
}

template <typename T>
typename MList<T>::ListRef MList<T>::getList()
{
	return this->mList;
}

template <typename T>
int MList<T>::getUniqueId()
{
	return this->mUniqueId;
}

template <typename T>
void MList<T>::setUniqueId(int value)
{
	this->mUniqueId = value;
}

template <typename T>
void MList<T>::add(T item)
{
	this->mList.push_back(item);
}

template <typename T>
bool MList<T>::remove(T item)
{
	UtilVector::Remove(this->mList, item);
	return true;
}

template <typename T>
typename MList<T>::ValueTypeRef MList<T>::operator [] (int index)
{
	return this->mList[index];
}

template <typename T>
void MList<T>::clear()
{
	this->mList.clear();
}

template <typename T>
int MList<T>::count()
{
	return this->mList.size();
}

template <typename T>
void MList<T>::removeAt(int index)
{
	UtilVector::RemoveAt(this->mList, index);
}

template <typename T>
int MList<T>::indexOf(T item)
{
	return UtilVector::IndexOf(this->mList, item);
}

template <typename T>
void MList<T>::insert(int index, T item)
{
	if (index <= this->count())
	{
		UtilVector::Insert(this->mList, index, item);
	}
	else
	{
		GLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, this->count()));
	}
}

template <typename T>
bool MList<T>::contains(T item)
{
	return this->indexOf(item) != -1;
}

MY_END_NAMESPACE