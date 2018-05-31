#ifndef __MList_H
#define __MList_H

#include <vector>
// TODO:
//#include "Prequisites.h"	// TODO: �������һ�������ļ������� UiMgr.h  TMList<UiFormId> mTmpList; ��һ�б�����󣬷���ʹ�� TMList �Ķ��ᱨ���ݹ�������µĴ���
#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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
		if (index <= count())
		{
			UtilVector::Insert(mList, index, item);
		}
		else
		{
			GLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, count()));
		}
	}

	bool contains(T item)
	{
		return indexOf(item) != -1;
	}
};

MY_END_NAMESPACE

#endif