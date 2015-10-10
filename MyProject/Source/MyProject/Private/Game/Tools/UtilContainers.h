#ifndef __UtilContainers_H
#define __UtilContainers_H

//==================== vector 区域 ===================

#include <vector>

/**
 *@brief 主要是一些容器辅助功能
 */
class UtilVector
{
public:
	// 查找向量某个元素索引，如果没有查找到就返回 -1
	template<class T>
	static int IndexOf(std::vector<T>& vec, T& item)
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

	// 移除一个元素，如果移除成功，就返回 true
	template<class T>
	static bool Remove(std::vector<T>& vec, T& item)
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
};

//=================== map 区域 ========================

#include <map>

class UtilMap
{
public:
	// 查找 map 中某个 key 是否存在
	template<class TKey, class TValue>
	static bool ContainsKey(std::map<TKey, TValue>& map, TKey& key)
	{
		std::map<TKey, TValue>::iterator iter = map.find(key);
		if (map.end() != iter)
		{
			return true;
		}
		return false;
	}

	// 删除某个 key
	template<class TKey, class TValue>
	static bool Remove(std::map<TKey, TValue>& map, TKey& key)
	{
		std::map<TKey, TValue>::iterator iter = map.find(key);
		if (map.end() != iter)
		{
			map.erase(iter);
			return true;
		}
		return false;
	}
};

#endif