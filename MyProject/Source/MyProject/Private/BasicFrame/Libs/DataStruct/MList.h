#ifndef __MList_H
#define __MList_H

#include <vector>
// TODO:
//#include "Common.h"	// TODO: �������һ�������ļ������� UIMgr.h  TMList<UIFormID> m_tmpList; ��һ�б�����󣬷���ʹ�� TMList �Ķ��ᱨ���ݹ�������µĴ���
#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"

/**
* @brief ��ϵͳ List �ķ�װ
*/
template <typename T>
class MList
{
public:
	typedef typename std::vector<T>::iterator Ite;

protected:
	std::vector<T> m_list;
	int m_uniqueId;       // Ψһ Id ������ʹ��

public:
	MList()
	{

	}

	MList(int capacity)
		: m_list(capacity)
	{

	}

	~MList()
	{

	}

	std::vector<T>& getList()
	{
		return m_list;
	}

	int getUniqueId()
	{
		return m_uniqueId;
	}

	void setUniqueId(int value)
	{
		m_uniqueId = value;
	}

	void Add(T item)
	{
		m_list.push_back(item);
	}

	bool Remove(T item)
	{
		UtilVector::Remove(m_list, item);
		return true;
	}

	T& operator [] (int index)
	{
		return m_list[index];
	}

	void Clear()
	{
		m_list.clear();
	}

	int Count()
	{
		return m_list.size();
	}

	void RemoveAt(int index)
	{
		UtilVector::RemoveAt(m_list, index);
	}

	int IndexOf(T item)
	{
		return UtilVector::IndexOf(m_list, item);
	}

	void Insert(int index, T item)
	{
		if (index <= Count())
		{
			UtilVector::Insert(m_list, index, item);
		}
		else
		{
			GLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, Count()));
		}
	}

	bool Contains(T item)
	{
		return IndexOf(item) != -1;
	}
};

#endif