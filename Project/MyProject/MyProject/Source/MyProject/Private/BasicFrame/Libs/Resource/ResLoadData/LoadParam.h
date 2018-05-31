#ifndef __LoadParam_H
#define __LoadParam_H

#include "IPoolObject.h"
#include "ResPackType.h"
#include "ResLoadType.h"
#include <string>
#include "EventDispatchDelegate.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ResItem;
class ResInsBase;

class LoadParam : public IPoolObject
{
public:
	std::string mPath;                  // 资源路径，传递进来都是完成的路径，都是相对 Prefabs\Resources 开始的，例如 Table\CardBase_client.txt，然后内部解析后

protected:
	std::string mOrigPath;                   // 原始资源加载目录，主要是打包的时候使用
	std::string mResUniqueId;
	//std::string mPath;                  // 资源路径，传递进来都是完成的路径，都是相对 Prefabs\Resources 开始的，例如 Table\CardBase_client.txt，然后内部解析后

	std::string mPathNoExt;             // 这个数据变成了从 Resources 目录开始，没有扩展名字，打包的包名字在包加载的时候判断
	std::string mExtName;      // 加载的资源的扩展名字

	std::string mPrefabName;         // 预设的名字，就是文件名字，没有路径和扩展名字
	std::string mLvlName;               // 关卡名字

	ResPackType mResPackType;           // 加载资源的类型
    ResLoadType mResLoadType;           // 资源加载类型

	std::string mSubPath;               // 子目录，可能一个包中有多个资源
	std::string mVersion;               // 加载的资源的版本号
	EventDispatchDelegate mLoadEventHandle;    // 加载事件回调函数

	bool mIsResNeedCoroutine;      // 资源是否需要协同程序
	bool mIsLoadNeedCoroutine;     // 加载是否需要协同程序

	std::string mPakPath;                   // 打包的资源目录，如果打包， mPakPath 应该就是 mPath

	ResItem* mLoadRes;
	ResInsBase* mLoadInsRes;

public:
	LoadParam();
	virtual ~LoadParam();

public:
	void init();

	void setPath(std::string value);
	std::string getPath();

	void setResUniqueId(std::string value);
	std::string getResUniqueId();

	void setOrigPath(std::string value);
	std::string getOrigPath();

	void setPathNoExt(std::string value);
	std::string getPathNoExt();

	void setResPackType(ResPackType value);
	ResPackType getResPackType();

	void setResLoadType(ResLoadType value);
	ResLoadType getResLoadType();

	void setIsResNeedCoroutine(bool value);
	bool getIsResNeedCoroutine();

	void setIsLoadNeedCoroutine(bool value);
	bool getIsLoadNeedCoroutine();

	void setLoadEventHandle(EventDispatchDelegate value);
	EventDispatchDelegate getLoadEventHandle();

	void setPrefabName(std::string value);
	std::string getPrefabName();
	void setExtName(std::string value);
	std::string getExtName();
	void setLvlName(std::string value);
	std::string getLvlName();

	void setLoadRes(ResItem* value);
	ResItem* getLoadRes();

	void setLoadInsRes(ResInsBase* value);
	ResInsBase* getLoadInsRes();

	void resetDefault();          // 将数据清空，有时候上一次调用的时候的参数 m_loaded 还在，结果被认为是这一次的回调了
    // 解析目录
	void resolvePath();
	void resolveLevel();
};

MY_END_NAMESPACE

#endif