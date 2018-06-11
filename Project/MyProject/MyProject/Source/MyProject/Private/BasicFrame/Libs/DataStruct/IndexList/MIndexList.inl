#include "MyProject.h"
#include "MIndexList.h"

MY_BEGIN_NAMESPACE(MyNS)

template <class T>
MIndexList::MIndexList()
{
	this->mEleTotal = 0;
	this->mList = new MList<T>();
	this->mIsOpKeepSort = false;
}

template <class T>
MIndexList::MIndexList(int capacity)
{
	//this->mList = new MList<T>(capacity);
	//this->mEleTotal = capacity;
}

template <class T>
void MIndexList::setIsOpKeepSort(bool value)
{
	this->mIsOpKeepSort = value;
}

//T[] ToArray()
//{
//    return this->mList.ToArray();
//}

template <class T>
MList<T> MIndexList::getList()
{
	return this->mList;
}

template <class T>
int MIndexList::getUniqueId()
{
	return this->mUniqueId;
}

template <class T>
void MIndexList::setUniqueId(int value)
{
	this->mUniqueId = value;
}

template <class T>
void MIndexList::add(T item)
{
	this->mList.add(item);
	this->mEleTotal += 1;
}

// 主要是 Add 一个 float 类型的 Vector3
template <class T>
void MIndexList::add(T item_1, T item_2, T item_3)
{
	this->add(item_1);
	this->add(item_2);
	this->add(item_3);
}

// 主要是 Add 一个 float 类型的 UV
template <class T>
void MIndexList::add(T item_1, T item_2)
{
	this->add(item_1);
	this->add(item_2);
}

// 主要是 Add 一个 byte 类型的 Color32
template <class T>
void MIndexList::add(T item_1, T item_2, T item_3, T item_4)
{
	this->add(item_1);
	this->add(item_2);
	this->add(item_3);
	this->add(item_4);
}

template <class T>
bool MIndexList::remove(T item)
{
	return this->_effectiveRemove(item);
}

template <class T>
T& MIndexList::operator[] (int index)
{
	return this->mList[index];
}

template <class T>
T MIndexList::get(int index)
{
	return this->mList[index];
}

template <class T>
void MIndexList::set(int index, T value)
{
	if(nullptr != this->mList[index])
	{
		this->mList[index].resetIndex();
	}

	this->mList[index] = value;
	this->mList[index].setIndex(index);
}

template <class T>
void MIndexList::clear()
{
	int index = 0;
	int listLen = this->mEleTotal;

	while(index < listLen)
	{
		this->mList[index].resetIndex();

		index += 1;
	}

	this->mList.Clear();
	this->mEleTotal = 0;
}

template <class T>
int MIndexList::count()
{
	//return this->mList.Count;
	return this->mEleTotal;
}

template <class T>
void MIndexList::setLength(int value)
{
	//this->mList.Capacity = value;
}

template <class T>
void MIndexList::removeAt(int index)
{
	if (index < this->count())
	{
		this->mList[index].resetIndex();
		this->mList.RemoveAt(index);
		this->mEleTotal -= 1;
	}
}

template <class T>
int MIndexList::indexOf(T item)
{
	if(item.getIndex() < this->count())
	{
		return item.getIndex();
	}

	return -1;
}

template <class T>
void MIndexList::insert(int index, T item)
{
	if (index <= this->count())
	{
		this->mList.Insert(index, item);
		item.setIndex(index);
		this->mEleTotal += 1;
		this->_updateIndex(index + 1);
	}
}

template <class T>
bool MIndexList::contains(T item)
{
	return item.getIndex() != -1;
}

//void sort(System.Comparison<T> comparer)
//{
//	this->mList.Sort(comparer);
//}

//void merge(MList<T> appendList)
//{
//	if(appendList != nullptr)
//	{
//		foreach(T item in appendList.list())
//		{
//			this->mList.Add(item);
//			item.setIndex(this->mEleTotal);
//			this->mEleTotal += 1;
//		}
//	}
//}

// 快速移除元素
template <class T>
bool MIndexList::_effectiveRemove(T item)
{
	bool ret = false;

	int index = item.getIndex();

	if (-1 != index)
	{
		ret = true;

		if (index == this->count() - 1)    // 如果是最后一个元素，直接移除
		{
			this->removeAt(index);
		}
		else
		{
			if (!this->mIsOpKeepSort)
			{
				this->mList[index] = this->mList[this->count() - 1];
				this->removeAt(this->count() - 1);
			}
			else
			{
				this->removeAt(index);
				this->_updateIndex(index);
			}
		}
	}

	return ret;
}

template <class T>
void MIndexList::_updateIndex(int index)
{
	int len = this->count();

	while(index < len)
	{
		this->mList[index].setIndex(index);

		++index;
	}
}

MY_END_NAMESPACE