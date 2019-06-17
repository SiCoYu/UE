#ifndef __MDiscreteList_H
#define __MDiscreteList_H

#include <list>
// TODO:
//#include "Prequisites.h"	// TODO: �������һ�������ļ������� UiMgr.h  TMList<UiFormId> mTmpList; ��һ�б�����󣬷���ʹ�� MList �Ķ��ᱨ���ݹ�������µĴ���
#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"
#include "GContainerObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief ��ϵͳ List �ķ�װ
*/
template <typename T>
class MDiscreteList : GContainerObject
{
public:
	typedef std::list<T> List;
	typedef std::list<T>& ListRef;
	typedef typename std::list<T>::iterator Iterator;
	typedef MDiscreteList<T>& MDiscreteListRef;
	typedef T& ValueTypeRef;

protected:
	std::list<T> mList;
	int mUniqueId;       // Ψһ Id ������ʹ��

public:
	MDiscreteList();
	MDiscreteList(int capacity);
	~MDiscreteList();

	void init();
	void dispose();

	ListRef getList();
	int getUniqueId();
	void setUniqueId(int value);

	T& get(int index);
	void set(int index, T& item);
	void add(T& item);
	bool remove(T& item);
	T& operator [] (int index);
	void clear();
	int count();
	void removeAt(int index);
	int indexOf(T& item);
	void insert(int index, T& item);
	bool contains(T& item);
};

MY_END_NAMESPACE

#include "MDiscreteList.inl"

#endif