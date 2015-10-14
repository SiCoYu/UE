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
	static int IndexOf(std::vector<T>& vec, T& item);

	// �Ƴ�һ��Ԫ�أ�����Ƴ��ɹ����ͷ��� true
	template<class T>
	static bool Remove(std::vector<T>& vec, T& item);

	// �Ƴ�ָ����������Ԫ��
	template<class T>
	static void RemoveAt(std::vector<T>& vec, int index);

	// ��ָ������λ�ò���һ��ֵ
	template<class T>
	static void Insert(std::vector<T>& vec, int index, T& item);
};

//=================== map ���� ========================

#include <map>

class UtilMap
{
public:
	// ���� map ��ĳ�� key �Ƿ����
	template<class TKey, class TValue>
	static bool ContainsKey(std::map<TKey, TValue>& map, TKey& key);

	// ɾ��ĳ�� key
	template<class TKey, class TValue>
	static bool Remove(std::map<TKey, TValue>& map, TKey& key);
};

//================== ʵ������ ====================
#include "UtilContainers.inl"


#endif