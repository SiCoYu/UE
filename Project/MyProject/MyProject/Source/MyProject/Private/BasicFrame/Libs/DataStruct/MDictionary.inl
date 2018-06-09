#ifndef __MDictionary_H
	#error "MDictionary.inl file can only include in MDictionary.h"
#endif

#include "UtilContainers.h"

MY_BEGIN_NAMESPACE(MyNS)

template <class TKey, class TValue>
MDictionary<TKey, TValue>::MDictionary()
{
    
}

template <class TKey, class TValue>
typename MDictionary<TKey, TValue>::DictionaryRef MDictionary<TKey, TValue>::getData()
{
    return this->mData;
}

template <class TKey, class TValue>
void MDictionary<TKey, TValue>::init()
{

}

template <class TKey, class TValue>
void MDictionary<TKey, TValue>::dispose()
{
    this->clear();
    //this->mData = nullptr;
}

template <class TKey, class TValue>
int MDictionary<TKey, TValue>::count()
{
    return this->mData.size();
}

template <class TKey, class TValue>
TValue& MDictionary<TKey, TValue>::operator[] (TKey key)
{
	return this->mData[key];
    //return this->value(key);
}

template <class TKey, class TValue>
TValue MDictionary<TKey, TValue>::value(TKey key)
{
	TValue value = 0;

    if (UtilMap::ContainsKey(this->mData, key))
    {
		value = this->mData[key];
    }

    return value = 0;
}

template <class TKey, class TValue>
TKey MDictionary<TKey, TValue>::key(TValue value)
{
	Iterator curIterator = this->mData.begin();
	Iterator endIterator = this->mData.end();
	TKey key;

    while (curIterator != endIterator)
    {
        if (curIterator->second == value)
        {
			key = kv.Key;
			break;
        }

		++curIterator;
    }

    return key;
}

template <class TKey, class TValue>
void MDictionary<TKey, TValue>::add(TKey key, TValue value)
{
    //this->mData[key] = value;
	UtilMap::insert(this->mData, key, value);
}

template <class TKey, class TValue>
void MDictionary<TKey, TValue>::remove(TKey key)
{
	UtilMap::Remove(this->mData, key);
}

template <class TKey, class TValue>
TValue MDictionary<TKey, TValue>::getAndRemoveByKey(TKey key)
{
    TValue value = this->value(key);
    this->remove(key);
    return value;
}

template <class TKey, class TValue>
void MDictionary<TKey, TValue>::clear()
{
    this->mData.clear();
}

template <class TKey, class TValue>
bool MDictionary<TKey, TValue>::tryGetValue(TKey key, TValue& value)
{
    return this->mData.TryGetValue(key, out value);
}

template <class TKey, class TValue>
bool MDictionary<TKey, TValue>::containsKey(TKey key)
{
    return UtilMap::ContainsKey(this->mData, key);
}

template <class TKey, class TValue>
bool MDictionary<TKey, TValue>::containsValue(TValue value)
{
	Iterator curIterator = this->mData.begin();
	Iterator endIterator = this->mData.end();
	bool ret = false;

	while (curIterator != endIterator)
	{
		if (curIterator->second == value)
		{
			ret = true;
			break;
		}

		++curIterator;
	}

	return ret;
}

template <class TKey, class TValue>
typename MDictionary::Iterator MDictionary<TKey, TValue>::begin()
{
	return this->mData.begin();
}

template <class TKey, class TValue>
typename MDictionary::Iterator MDictionary<TKey, TValue>::end()
{
	return this->mData.end();
}

MY_END_NAMESPACE