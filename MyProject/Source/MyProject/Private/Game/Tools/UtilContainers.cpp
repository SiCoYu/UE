#include "MyProject.h"
#include "UtilContainers.h"

//==================== vector ÇøÓò ===================
template<class T>
int UtilVector::IndexOf(std::vector<T>& vec, T& item)
{
	int idx = -1;
	for (auto elem : vec)
	{
		if (elem == item)
		{
			break;
		}
	}

	return idx;
}

template<class T>
bool UtilVector::Remove(std::vector<T>& vec, T& item)
{
	std::vector<T>::iterator _beginIte;
	std::vector<T>::iterator _endIte;
	_beginIte = vec.begin();
	_endIte = vec.end();

	for (; _beginIte != _endIte; ++_beginIte)
	{
		if (*_beginIte == item)
		{
			vec.erase(_beginIte);
			return true;
		}
	}

	return false;
}

//=================== map ÇøÓò ========================

template<class TKey, class TValue>
bool UtilMap::ContainsKey(std::map<TKey, TValue>& map, TKey& key)
{
	std::map<TKey, TValue>::iterator iter = map.find(key);
	if (map.end() != iter)
	{
		return true;
	}
	return false;
}

template<class TKey, class TValue>
bool UtilMap::Remove(std::map<TKey, TValue>& map, TKey& item)
{
	std::map<TKey, TValue>::iterator iter = map.find(key);
	if (map.end() != iter)
	{
		map.erase(iter);
		return true;
	}
	return fasle
}