#ifndef __MDiscreteList_H
	#error "MDiscreteList.inl file can only include in MList.h"
#endif

#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template <typename T>
MDiscreteList<T>::MDiscreteList()
{

}

template <typename T>
MDiscreteList<T>::MDiscreteList(int capacity)
	: mList(capacity)
{

}

template <typename T>
MDiscreteList<T>::~MDiscreteList()
{

}

template <typename T>
void MDiscreteList<T>::init()
{

}

template <typename T>
void MDiscreteList<T>::dispose()
{
	this->clear();
}

template <typename T>
T& MDiscreteList<T>::get(int index)
{
	T* ret = nullptr;

	if (index < this->count())
	{
		ret = &(UtilList::At(this->mList, index));
	}

	return *ret;
}

template <typename T>
void MDiscreteList<T>::set(int index, T& item)
{
	if (index < this->count())
	{
		this->get(index) = item;
	}
}

template <typename T>
typename MDiscreteList<T>::ListRef MDiscreteList<T>::getList()
{
	return this->mList;
}

template <typename T>
int MDiscreteList<T>::getUniqueId()
{
	return this->mUniqueId;
}

template <typename T>
void MDiscreteList<T>::setUniqueId(int value)
{
	this->mUniqueId = value;
}

template <typename T>
void MDiscreteList<T>::add(T& item)
{
	UtilList::Add(this->mList, item);
}

template <typename T>
bool MList<T>::remove(T& item)
{
	UtilList::Remove(this->mList, item);
	return true;
}

template <typename T>
typename MDiscreteList<T>::ValueTypeRef MDiscreteList<T>::operator [] (int index)
{
	return this->get(index);
}

template <typename T>
void MDiscreteList<T>::clear()
{
	this->mList.clear();
}

template <typename T>
int MDiscreteList<T>::count()
{
	return this->mList.size();
}

template <typename T>
void MDiscreteList<T>::removeAt(int index)
{
	UtilList::RemoveAt(this->mList, index);
}

template <typename T>
int MDiscreteList<T>::indexOf(T& item)
{
	return UtilList::IndexOf(this->mList, item);
}

template <typename T>
void MDiscreteList<T>::insert(int index, T& item)
{
	if (index <= this->count())
	{
		UtilList::Insert(this->mList, index, item);
	}
	else
	{
		GLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, this->count()));
	}
}

template <typename T>
bool MDiscreteList<T>::contains(T& item)
{
	return this->indexOf(item) != -1;
}

MY_END_NAMESPACE