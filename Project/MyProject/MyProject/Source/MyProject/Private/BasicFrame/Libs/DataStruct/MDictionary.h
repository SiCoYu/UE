#ifndef __MDictionary_H
#define __MDictionary_H

#include <map>

template <class TKey, class TValue>
class MDictionary : GContainerObject
{
	typedef std::map<TKey, TValue> Dictionary;
	typedef std::map<TKey, TValue>::iterator Iterator;
	typedef std::pair<TKey, TValue> ItemType;

protected:
	std::map<TKey, TValue> mData;

public:
	MDictionary();
	Dictionary getData();

	void init();
	void dispose();
	int getCount();
	TValue operator[] (TKey key);
	TValue operator[] (TKey key, TValue value);

	TValue value(TKey key);
	TKey key(TValue value);
	int count();
	void add(TKey key, TValue value);
	void remove(TKey key);
	TValue getAndRemoveByKey(TKey key);
	void clear();
	bool tryGetValue(TKey key, out TValue value);
	bool containsKey(TKey key);
	bool containsValue(TValue value);
};

#include "MDictionary.inl"

#endif