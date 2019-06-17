#ifndef __MList_H
#define __MList_H

#include <vector>
// TODO:
//#include "Prequisites.h"	// TODO: 添加了这一样包含文件，导致 UiMgr.h  TMList<UiFormId> mTmpList; 这一行编译错误，凡是使用 TMList 的都会报错，递归包含导致的错误
#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"
#include "GContainerObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 对系统 List 的封装
*/
template <typename T>
class MList : GContainerObject
{
public:
	typedef std::vector<T> List;
	typedef std::vector<T>& ListRef;
	typedef typename std::vector<T>::iterator Iterator;
	typedef MList<T>& MListRef;
	typedef T& ValueTypeRef;

protected:
	std::vector<T> mList;
	int mUniqueId;       // 唯一 Id ，调试使用

public:
	MList();
	MList(int capacity);
	~MList();

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

#include "MList.inl"

#endif