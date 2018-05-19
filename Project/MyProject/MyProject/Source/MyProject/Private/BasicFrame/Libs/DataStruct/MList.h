#ifndef __MList_H
#define __MList_H

#include <vector>
// TODO:
//#include "Common.h"	// TODO: �������һ�������ļ������� UiMgr.h  TMList<UiFormId> mTmpList; ��һ�б�����󣬷���ʹ�� TMList �Ķ��ᱨ���ݹ�������µĴ���
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

	void add(T item)
	{
		mList.push_back(item);
	}

	bool remove(T item)
	{
		UtilVector::Remove(mList, item);
		return true;
	}

	T& operator [] (int index)
	{
		return mList[index];
	}

	void operator [] (int index, T& value)
	{
		mList[index] = value;
	}

	void clear()
	{
		mList.clear();
	}

	int count()
	{
		return mList.size();
	}

	void removeAt(int index)
	{
		UtilVector::RemoveAt(mList, index);
	}

	int indexOf(T item)
	{
		return UtilVector::IndexOf(mList, item);
	}

	void insert(int index, T item)
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

	bool contains(T item)
	{
		return indexOf(item) != -1;
	}
};

#endif