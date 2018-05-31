#ifndef __ResLoadData_H
#define __ResLoadData_H

#include <map>
#include <string>
#include <list>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LoadItem;
class ResItem;

class ResLoadData
{
    // 因为资源有些需要协同程序，因此重复利用资源
public:
	std::map<std::string, LoadItem*> mPath2LDItem;       // 正在加载的内容 loaditem
	std::list<LoadItem*> mWillLDItem;                           // 将要加载的 loaditem
	std::list<LoadItem*> mNoUsedLDItem;                         // 没有被使用的 loaditem
	std::map<std::string, ResItem*> mPath2Res;
	std::list<ResItem*> mNoUsedResItem;                         // 没有被使用的 Res

public:
	ResLoadData();
};

MY_END_NAMESPACE

#endif