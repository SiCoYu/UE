#ifndef __MDictionary_H
#define __MDictionary_H

#include <map>
#include "GContainerObject.h"

template <class TKey, class TValue>
class MDictionary : GContainerObject
{
public:
	typedef std::map<TKey, TValue> Dictionary;
	// error C4346: 'iterator': dependent name is not a type
	// typedef std::map<TKey, TValue>::iterator Iterator;
	typedef typename std::map<TKey, TValue>::iterator Iterator;
	typedef std::pair<TKey, TValue> ItemType;

protected:
	std::map<TKey, TValue> mData;

public:
	MDictionary();
	Dictionary getData();

	void init();
	void dispose();
	int getCount();
	TValue& operator[] (TKey key);

	TValue value(TKey key);
	TKey key(TValue value);
	int count();
	void add(TKey key, TValue value);
	void remove(TKey key);
	TValue getAndRemoveByKey(TKey key);
	void clear();
	bool tryGetValue(TKey key, TValue& value);
	bool containsKey(TKey key);
	bool containsValue(TValue value);
};

#include "MDictionary.inl"

#endif