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
	typedef std::vector<T> List;
	typedef std::vector<T>& ListRef;
	typedef typename std::vector<T>::iterator Iterator;
	typedef MList<T>& MListRef;
	typedef T& ItemRef;

protected:
	std::vector<T> mList;
	int mUniqueId;       // Ψһ Id ������ʹ��

public:
	MList();
	MList(int capacity);
	~MList();

	ListRef getList();
	int getUniqueId();
	void setUniqueId(int value);

	void add(T item);
	bool remove(T item);
	T& operator [] (int index);
	void clear();
	int count();
	void removeAt(int index);
	int indexOf(T item);
	void insert(int index, T item);
	bool contains(T item);
};

MY_END_NAMESPACE

#include "MList.inl"

#endif