#ifndef __ResLoadData_H
#define __ResLoadData_H

#include <map>
#include <string>
#include <list>

class LoadItem;
class ResItem;

class ResLoadData
{
    // 因为资源有些需要协同程序，因此重复利用资源
public:
	std::map<std::string, LoadItem*> m_path2LDItem;       // 正在加载的内容 loaditem
	std::list<LoadItem*> m_willLDItem;                           // 将要加载的 loaditem
	std::list<LoadItem*> m_noUsedLDItem;                         // 没有被使用的 loaditem
	std::map<std::string, ResItem*> m_path2Res;
	std::list<ResItem*> m_noUsedResItem;                         // 没有被使用的 Res

public:
	ResLoadData();
};

#endif