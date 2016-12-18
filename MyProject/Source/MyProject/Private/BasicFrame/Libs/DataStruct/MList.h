#ifndef __MList_H
#define __MList_H

#include <vector>
// TODO:
//#include "Common.h"	// TODO: �������һ�������ļ������� UIMgr.h  TMList<UIFormID> mTmpList; ��һ�б�����󣬷���ʹ�� TMList �Ķ��ᱨ���ݹ�������µĴ���
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
	std::vector<T> mList;
	int mUniqueId;       // Ψһ Id ������ʹ��

public:
	MList()
	{

	}

	MList(int capacity)
		: mList(capacity)
	{

	}

	~MList()
	{

	}

	std::vector<T>& getList()
	{
		return mList;
	}

	int getUniqueId()
	{
		return mUniqueId;
	}

	void setUniqueId(int value)
	{
		mUniqueId = value;
	}

	void Add(T item)
	{
		mList.push_back(item);
	}

	bool Remove(T item)
	{
		UtilVector::Remove(mList, item);
		return true;
	}

	T& operator [] (int index)
	{
		return mList[index];
	}

	void Clear()
	{
		mList.clear();
	}

	int Count()
	{
		return mList.size();
	}

	void RemoveAt(int index)
	{
		UtilVector::RemoveAt(mList, index);
	}

	int IndexOf(T item)
	{
		return UtilVector::IndexOf(mList, item);
	}

	void Insert(int index, T item)
	{
		if (index <= Count())
		{
			UtilVector::Insert(mList, index, item);
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