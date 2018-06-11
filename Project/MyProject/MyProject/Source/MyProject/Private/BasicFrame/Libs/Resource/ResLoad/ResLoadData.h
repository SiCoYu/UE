#ifndef __ResLoadData_H
#define __ResLoadData_H

#include "MDictionary.h"
#include <string>
#include <list>
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LoadItem;
class ResItem;

class ResLoadData : public GObject
{
public:
	typedef typename MDictionary<std::string, ResItem*>::Iterator Iterator;

    // 因为资源有些需要协同程序，因此重复利用资源
public:
	MDictionary<std::string, LoadItem*> mPath2LoadItemDic;       // 正在加载的内容 loaditem
	std::list<LoadItem*> mWillLoadItemList;                           // 将要加载的 loaditem
	std::list<LoadItem*> mNoUsedLoadItemList;                         // 没有被使用的 loaditem
	MDictionary<std::string, ResItem*> mPath2ResDic;
	std::list<ResItem*> mNoUsedResItemList;                         // 没有被使用的 Res

public:
	ResLoadData();

	void init();
	void dispose();
};

MY_END_NAMESPACE

#endif