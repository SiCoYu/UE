#ifndef __UtilContainers_H
#error "UtilContainers.inl file can only include in UtilContainers.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

//==================== vector 区域 ===================
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

template<class T>
void UtilVector::RemoveAt(std::vector<T>& vec, int index)
{
	if (index < vec.size())
	{
		std::vector<T>::iterator _beginIte;
		_beginIte = vec.begin();
		std::advance(_beginIte, index);
		vec.erase(_beginIte);
	}
}

template<class T>
void UtilVector::Insert(std::vector<T>& vec, int index, T& item)
{
	if (index < vec.size())
	{
		std::vector<T>::iterator _beginIte;
		_beginIte = vec.begin();
		std::advance(_beginIte, index);
		vec.insert(_beginIte, item);
	}
}

template<class T>
void UtilVector::Add(std::vector<T>& vec, T& item)
{
	vec.push_back(item);
}

//================== list 区域 =========================
template<class T>
bool UtilList::Remove(std::list<T>& list, T& item)
{
	std::list<T>::iterator _beginIte;
	std::list<T>::iterator _endIte;
	_beginIte = list.begin();
	_endIte = list.end();

	for (; _beginIte != _endIte; ++_beginIte)
	{
		if (*_beginIte == item)
		{
			list.erase(_beginIte);
			return true;
		}
	}

	return false;
}

template<class T>
void UtilList::RemoveAt(std::list<T>& list, int index)
{
	if (index < list.size())
	{
		std::list<T>::iterator _beginIte;
		_beginIte = list.begin();
		std::advance(_beginIte, index);
		list.erase(_beginIte);
	}
}

template<class T>
int UtilList::Count(std::list<T>& list)
{
	return list.size();
}

template<class T>
int UtilList::Add(std::list<T>& list, T& item)
{
	list.push_back(item);
	return 0;
}

//template<class T>
//T& UtilList::operator[](std::list<T>& list, int index)
//{
//	if (index < list.size())
//	{
//		std::list<T>::iterator _beginIte;
//		_beginIte = list.begin();
//		std::advance(_beginIte, index);
//		return *_beginIte;
//	}
//
//	// 返回一个引用
//	static T m_defRef;		// 必须有一个默认的构造函数
//	return m_defRef;
//}

template<class T>
T& UtilList::At(std::list<T>& list, int index)
{
	if (index < list.size())
	{
		std::list<T>::iterator _beginIte;
		_beginIte = list.begin();
		std::advance(_beginIte, index);
		return *_beginIte;
	}
	
	// 返回一个引用
	static T m_defRef;		// 必须有一个默认的构造函数
	return m_defRef;
}

//=================== map 区域 ========================

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
bool UtilMap::Remove(std::map<TKey, TValue>& map, TKey& key)
{
	std::map<TKey, TValue>::iterator iter = map.find(key);
	if (map.end() != iter)
	{
		map.erase(iter);
		return true;
	}
	return false;
}

MY_END_NAMESPACE