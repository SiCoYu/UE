#ifndef __ResLoadData_H
#define __ResLoadData_H

#include "MDictionary.h"
#include <string>
#include "MDiscreteList.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LoadItem;
class ResItem;

class ResLoadData : public GObject
{
public:
	typedef typename MDictionary<std::string, ResItem*>::Iterator ResItemIterator;
	typedef typename MDictionary<std::string, LoadItem*>::Iterator LoadItemIterator;

    // 因为资源有些需要协同程序，因此重复利用资源
public:
	MDictionary<std::string, LoadItem*> mPath2LoadItemDic;       // 正在加载的内容 loaditem
	MDiscreteList<LoadItem*> mWillLoadItemList;                           // 将要加载的 loaditem
	MDiscreteList<LoadItem*> mNoUsedLoadItemList;                         // 没有被使用的 loaditem
	MDictionary<std::string, ResItem*> mPath2ResDic;
	MDiscreteList<ResItem*> mNoUsedResItemList;                         // 没有被使用的 Res

public:
	ResLoadData();

	void init();
	void dispose();
};

MY_END_NAMESPACE

#endif