#ifndef __InsResMgrBase_H
#define __InsResMgrBase_H

#include <map>
#include <string>
#include "MList.h"
#include "EventDispatchDelegate.h"
#include "LoadParam.h"
#include "UtilContainers.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "InsResBase.h"
#include "ResEventDispatch.h"
#include "RefCount.h"
//#include "Common.h"	// TODO: 包含这个就导致 UIAssetMgr 报错 InsResMgrBase 不能识别，因此只包含必要的头文件，递归包含导致的错误
#include "Ctx.h"
#include "ResLoadMgr.h"
#include "PoolSys.h"
#include "LogSys.h"

class InsResBase;
class IDispatchObject;

/**
 * @brief 资源管理器，不包括资源加载
 */
class InsResMgrBase
{
public:
	std::map<std::string, InsResBase*> mPath2ResDic;

protected:
	MList<std::string> mZeroRefResIDList;      // 没有引用的资源 ID 列表
    int mLoadingDepth;          // 加载深度

public:
	InsResMgrBase();
	virtual ~InsResMgrBase();

	virtual void init();
	virtual void dispose();

	template<class T>
	T* getAndSyncLoad(std::string path, EventDispatchDelegate handle = nullptr);

	template<class T>
	T* getAndAsyncLoad(std::string path, EventDispatchDelegate handle);

	template<class T>
	T* getAndLoad(LoadParam* param);

	// 同步加载，立马加载完成，并且返回加载的资源， syncLoad 同步加载资源不能和异步加载资源的接口同时去加载一个资源，如果异步加载一个资源，这个时候资源还没有加载完成，然后又同步加载一个资源，这个时候获取的资源是没有加载完成的，由于同步加载资源没有回调，因此即使同步加载的资源加载完成，也不可能获取加载完成事件
	template<class T>
	void syncLoad(std::string path, EventDispatchDelegate handle = nullptr);

	template<class T>
	T* createResItem(LoadParam* param);

protected:
	void loadWithResCreatedAndLoad(LoadParam* param);

	template<class T>
	void loadWithResCreatedAndNotLoad(LoadParam* param, T* resItem);

	template<class T>
	void loadWithNotResCreatedAndNotLoad(LoadParam* param);

public:
	// TODO:
	//virtual void load(LoadParam* param);	// 模板函数不能使虚函数
	template<class T>
	void load(LoadParam* param);

	virtual void unload(std::string path, EventDispatchDelegate loadEventHandle);

protected:
	// 添加无引用资源到 List
	void addNoRefResID2List(std::string path);
    // 卸载没有引用的资源列表中的资源
	void unloadNoRefResFromList();
	void unloadNoRef(std::string path);

public:
	virtual void onLoadEventHandle(IDispatchObject* dispObj);
	InsResBase* getRes(std::string path);
    // 卸载所有的资源
	void unloadAll();
};

#include "InsResMgrBase.inl"

#endif