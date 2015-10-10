#ifndef __UtilContainers_H
#define __UtilContainers_H

//==================== vector ���� ===================

#include <vector>

/**
 *@brief ��Ҫ��һЩ������������
 */
class UtilVector
{
public:
	// ��������ĳ��Ԫ�����������û�в��ҵ��ͷ��� -1
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

	// �Ƴ�һ��Ԫ�أ�����Ƴ��ɹ����ͷ��� true
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

//=================== map ���� ========================

#include <map>

class UtilMap
{
public:
	// ���� map ��ĳ�� key �Ƿ����
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

	// ɾ��ĳ�� key
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