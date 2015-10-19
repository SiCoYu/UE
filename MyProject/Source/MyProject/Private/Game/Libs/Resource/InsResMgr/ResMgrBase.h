#ifndef __ResMgrBase_H
#define __ResMgrBase_H

#include <map>
#include <string>
#include "MList.h"

class InsResBase;

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
	T getAndSyncLoad<T>(string path);
	template<class T>
	T getAndAsyncLoad<T>(string path, Action<IDispatchObject> handle);
	template<class T>
	T getAndLoad<T>(LoadParam param);

    // 同步加载，立马加载完成，并且返回加载的资源， syncLoad 同步加载资源不能喝异步加载资源的接口同时去加载一个资源，如果异步加载一个资源，这个时候资源还没有加载完成，然后又同步加载一个资源，这个时候获取的资源是没有加载完成的，由于同步加载资源没有回调，因此即使同步加载的资源加载完成，也不可能获取加载完成事件
	template<class T>
	void syncLoad<T>(string path);
	template<class T>
	T createResItem<T>(LoadParam param);
protected:
	void loadWithResCreatedAndLoad(LoadParam param);
	template<class T>
	void loadWithResCreatedAndNotLoad<T>(LoadParam param, T resItem);
	template<class T>
	void loadWithNotResCreatedAndNotLoad<T>(LoadParam param);

public:
	template<class T>
	virtual void load<T>(LoadParam param);
	virtual void unload(string path, Action<IDispatchObject> loadEventHandle);
    // 添加无引用资源到 List
protected:
	void addNoRefResID2List(string path)
    {
        m_zeroRefResIDList.Add(path);
    }

    // 卸载没有引用的资源列表中的资源
	void unloadNoRefResFromList();
	void unloadNoRef(string path);
public:
	virtual void onLoadEventHandle(IDispatchObject dispObj);
	object getRes(string path);
    // 卸载所有的资源
	void unloadAll();
};

#endif