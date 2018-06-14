#ifndef __MDictionary_H
#define __MDictionary_H

#include <map>
#include "GContainerObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template <class TKey, class TValue>
class MDictionary : GContainerObject
{
public:
	typedef std::map<TKey, TValue> Dictionary;
	typedef std::map<TKey, TValue>& DictionaryRef;
	// error C4346: 'iterator': dependent name is not a type
	// typedef std::map<TKey, TValue>::iterator Iterator;
	typedef typename std::map<TKey, TValue>::iterator Iterator;
	typedef std::pair<TKey, TValue> ItemType;
	typedef MDictionary<TKey, TValue>& MDictionaryRef;

protected:
	std::map<TKey, TValue> mData;

public:
	MDictionary();
	DictionaryRef getData();

	void init();
	void dispose();
	int count();
	TValue&& operator[] (TKey&& key);

	TValue& value(TKey& key);
	TKey& key(TValue& value);
	void add(TKey& key, TValue& value);
	void remove(TKey& key);
	TValue& getAndRemoveByKey(TKey& key);
	void clear();
	bool tryGetValue(TKey& key, TValue& value);
	bool containsKey(TKey& key);
	bool containsValue(TValue& value);

	Iterator begin();
	Iterator end();
};

MY_END_NAMESPACE

#include "MDictionary.inl"

#endif