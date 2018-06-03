#include "MyProject.h"
#include "MKeyIndexList.h"

MY_BEGIN_NAMESPACE(MyNS)

template <class TKey, class TValue>
MKeyIndexList::MKeyIndexList()
{
	//this->mList = new MList<TValue>();
	this->mList.setIsSpeedUpFind(true);
	this->mList.setIsOpKeepSort(true);

	//this->mIndexDic = new MDictionary<TKey, TValue>();
}

template <class TKey, class TValue>
void MKeyIndexList::clear()
{
	this->mList.clear();
	this->mIndexDic.clear();
}

template <class TKey, class TValue>
MList<TValue> MKeyIndexList::getList()
{
	return this->mList;
}

template <class TKey, class TValue>
TValue MKeyIndexList::get(int index)
{
	return this->mList.get(index);
}

template <class TKey, class TValue>
MDictionary<TKey, TValue> MKeyIndexList::getIndexDic()
{
	return this->mIndexDic;
}

template <class TKey, class TValue>
void MKeyIndexList::add(TKey key, TValue value)
{
	if(!this->mIndexDic.containsKey(key))
	{
		this->mList.add(value);
		this->mIndexDic.add(key, value);
	}
}

template <class TKey, class TValue>
void MKeyIndexList::addToFirst(TKey key, TValue value)
{
	this->mList.insert(0, value);
	this->mIndexDic.add(key, value);
}

template <class TKey, class TValue>
void MKeyIndexList::addToSecond(TKey key, TValue value)
{
	this->mList.insert(1, value);
	this->mIndexDic.add(key, value);
}

template <class TKey, class TValue>
void MKeyIndexList::remove(TKey key)
{
	if(this->mIndexDic.containsKey(key))
	{
		this->mList.remove(this->mIndexDic.value(key));
		this->mIndexDic.remove(key);
	}
}

template <class TKey, class TValue>
TValue MKeyIndexList::getAndRemoveByKey(TKey key)
{
	TValue item = this->value(key);
	this->remove(key);
	return item;
}

template <class TKey, class TValue>
TValue MKeyIndexList::value(TKey key)
{
	TValue ret = nullptr;

	if(this->mIndexDic.containsKey(key))
	{
		ret = this->mIndexDic.value(key);
	}

	return ret;
}

template <class TKey, class TValue>
int MKeyIndexList::count()
{
	return this->mList.count();
}

template <class TKey, class TValue>
bool MKeyIndexList::containsKey(TKey key)
{
	return this->mIndexDic.containsKey(key);
}

MY_END_NAMESPACE