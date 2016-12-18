#ifndef __LoadParam_H
#define __LoadParam_H

#include "IRecycle.h"
#include "ResPackType.h"
#include "ResLoadType.h"
#include <string>
#include "EventDispatchDelegate.h"

class ResItem;
class InsResBase;

class LoadParam : public IRecycle
{
protected:
	std::string m_prefabName;         // 预设的名字，就是文件名字，没有路径和扩展名字
	std::string m_extName;      // 加载的资源的扩展名字

	std::string m_lvlName;               // 关卡名字

public:
	ResPackType m_resPackType;           // 加载资源的类型
    ResLoadType mResLoadType;           // 资源加载类型

    std::string m_path;                  // 资源路径，传递进来都是完成的路径，都是相对 Prefabs\Resources 开始的，例如 Table\CardBase_client.txt，然后内部解析后
	std::string m_subPath;               // 子目录，可能一个包中有多个资源
	std::string m_pathNoExt;             // 这个数据变成了从 Resources 目录开始，没有扩展名字，打包的包名字在包加载的时候判断
	std::string m_version;               // 加载的资源的版本号
	EventDispatchDelegate m_loadEventHandle;    // 加载事件回调函数

	bool m_resNeedCoroutine;      // 资源是否需要协同程序
	bool m_loadNeedCoroutine;     // 加载是否需要协同程序

	std::string m_origPath;                   // 原始资源加载目录，主要是打包的时候使用
	std::string m_pakPath;                   // 打包的资源目录，如果打包， m_pakPath 应该就是 m_path

	ResItem* m_loadRes;
	InsResBase* m_loadInsRes;

public:
	std::string getPrefabName();
	std::string getExtName();
	std::string getLvlName();
	void resetDefault();          // 将数据清空，有时候上一次调用的时候的参数 m_loaded 还在，结果被认为是这一次的回调了
    // 解析目录
	void resolvePath();
	void resolveLevel();
};

#endif