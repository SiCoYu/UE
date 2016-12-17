#ifndef __ResMgrBase_H
#define __ResMgrBase_H

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
//#include "Common.h"	// TODO: 包含这个就导致 UIAssetMgr 报错 ResMgrBase 不能识别，因此只包含必要的头文件，递归包含导致的错误
#include "Ctx.h"
#include "ResLoadMgr.h"
#include "PoolSys.h"
#include "LogSys.h"

class InsResBase;
class IDispatchObject;

/**
 * @brief 资源管理器，不包括资源加载
 */
class ResMgrBase
{
public:
	std::map<std::string, InsResBase*> m_path2ResDic;

protected:
	MList<std::string> m_zeroRefResIDList;      // 没有引用的资源 ID 列表
    int m_loadingDepth;          // 加载深度

public:
	ResMgrBase();

	template<class T>
	T* getAndSyncLoad(std::string path)
	{
		syncLoad<T>(path);
		return (T*)getRes(path);
	}

	template<class T>
	T* getAndAsyncLoad(std::string path, EventDispatchDelegate handle)
	{
		T* ret = nullptr;
		LoadParam* param = GPoolSys->newObject<LoadParam>();
		LocalFileSys.modifyLoadParam(path, param);
		param.m_loadNeedCoroutine = true;
		param.m_resNeedCoroutine = true;
		param.m_loadEventHandle = handle;
		ret = getAndLoad<T>(param);
		GPoolSys->deleteObj(param);

		return ret;
	}

	template<class T>
	T* getAndLoad(LoadParam* param)
	{
		load<T>(param);
		return (T*)getRes(param.m_path);
	}

	// 同步加载，立马加载完成，并且返回加载的资源， syncLoad 同步加载资源不能喝异步加载资源的接口同时去加载一个资源，如果异步加载一个资源，这个时候资源还没有加载完成，然后又同步加载一个资源，这个时候获取的资源是没有加载完成的，由于同步加载资源没有回调，因此即使同步加载的资源加载完成，也不可能获取加载完成事件
	template<class T>
	void syncLoad(std::string path)
	{
		LoadParam param;
		param = GPoolSys->newObject<LoadParam>();
		param->m_path = path;
		// param.m_loadEventHandle = onLoadEventHandle;        // 这个地方是同步加载，因此不需要回调，如果写了，就会形成死循环， InsResBase 中的 init 又会调用 onLoadEventHandle 这个函数，这个函数是外部回调的函数，由于同步加载，没有回调，因此不要设置这个 param.m_loadEventHandle = onLoadEventHandle ，内部会自动调用
		param->m_loadNeedCoroutine = false;
		param->m_resNeedCoroutine = false;
		load<T>(param);
		GPoolSys->deleteObj(param);
	}

	template<class T>
	T* createResItem(LoadParam* param)
	{
		T* ret = new T();
		ret->getRefCountResLoadResultNotify()->getRefCount()->incRef();
		ret->m_path = param->m_path;

		ret->getRefCountResLoadResultNotify()->getLoadResEventDispatch()->addEventHandle(param->m_loadEventHandle);

		return ret;
	}

protected:
	void loadWithResCreatedAndLoad(LoadParam* param);

	template<class T>
	void loadWithResCreatedAndNotLoad(LoadParam* param, T* resItem)
	{
		m_path2ResDic[param->m_path] = resItem;
		m_path2ResDic[param->m_path]->getRefCountResLoadResultNotify()->getResLoadState()->setLoading();
		param->m_loadEventHandle = EventDispatchDelegate(this, &ResMgrBase::onLoadEventHandle);
		GResLoadMgr->loadResources(param);
	}

	template<class T>
	void loadWithNotResCreatedAndNotLoad(LoadParam* param)
	{
		T* resItem = createResItem<T>(param);
		loadWithResCreatedAndNotLoad<T>(param, resItem);
	}

public:
	// TODO:
	//virtual void load(LoadParam* param);	// 模板函数不能使虚函数
	template<class T>
	void load(LoadParam* param)
	{
		++m_loadingDepth;
		if (UtilMap::ContainsKey(m_path2ResDic, param->m_path))
		{
			loadWithResCreatedAndLoad(param);
		}
		else if (param->m_loadInsRes != nullptr)
		{
			loadWithResCreatedAndNotLoad<T>(param, (T*)(param->m_loadInsRes));
		}
		else
		{
			loadWithNotResCreatedAndNotLoad<T>(param);
		}
		--m_loadingDepth;

		if (m_loadingDepth == 0)
		{
			unloadNoRefResFromList();
		}
	}

	virtual void unload(std::string path, EventDispatchDelegate loadEventHandle);
    // 添加无引用资源到 List
protected:
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

#endif