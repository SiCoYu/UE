#ifndef __ResLoadMgr_H
#define __ResLoadMgr_H

#include <string>

#include "MsgRouteHandleBase.h"
#include "Platform.h"
#include "MList.h"
#include "ResPackType.h"
#include "EventDispatchDelegate.h"
#include "IDispatchObject.h"
#include "TypeDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ResLoadData;
class LoadItem;
class ResItem;
class LoadParam;

class ResLoadMgr : public MsgRouteHandleBase, public IDispatchObject
{
protected:
	uint32 mMaxParral;                             // 最多同时加载的内容
    uint32 mCurNum;                                // 当前加载的数量
    ResLoadData* mLoadData;
    LoadItem* mRetLoadItem;
    ResItem* mRetResItem;
    //ResMsgRouteCB mResMsgRouteCB;
    MList<std::string> mZeroRefResIdList;      // 没有引用的资源 Id 列表
    int mLoadingDepth;      // 加载深度

public:
	ResLoadMgr();
	virtual ~ResLoadMgr();
	void init();
	void dispose();

    // 重置加载设置
protected:
	void resetLoadParam(LoadParam* loadParam);

public:
	void loadAsset(LoadParam* param);

	ResItem* getResource(std::string path);
	LoadItem* getLoadItem(std::string path);

	void loadData(LoadParam* param);
    // eBundleType 打包类型资源加载
	void loadBundle(LoadParam* param);
    // eLevelType 打包类型资源加载，都用协程加载
	void loadLevel(LoadParam* param);
    // eResourcesType 打包类型资源加载
	void loadResources(LoadParam* param);

	ResItem* createResItem(LoadParam* param);
	LoadItem* createLoadItem(LoadParam* param);

    // 资源创建并且正在被加载
	void loadWithResCreatedAndLoad(LoadParam* param);
	void loadWithResCreatedAndNotLoad(LoadParam* param, ResItem* resItem);
	void loadWithNotResCreatedAndNotLoad(LoadParam* param);
    // 通用类型，需要自己设置很多参数

public:
	void load(LoadParam* param);
	ResItem* getAndLoad(LoadParam* param);
    // 这个卸载有引用计数，如果有引用计数就卸载不了
	void unload(std::string path, EventDispatchDelegate loadEventHandle);
    // 添加无引用资源到 List

protected:
	void addNoRefResId2List(std::string path);
    // 卸载没有引用的资源列表中的资源
	void unloadNoRefResFromList();
    // 不考虑引用计数，直接卸载
	void unloadNoRef(std::string path);

public:
	void onLoadEventHandle(IDispatchObject* dispObj, uint eventId = 0);
	void onLoaded(LoadItem* item);
	void onFailed(LoadItem* item);

protected:
	void releaseLoadItem(LoadItem* item);
	void loadNextItem();
	ResItem* findResFormPool(ResPackType type);
	LoadItem* findLoadItemFormPool(ResPackType type);
    // 资源加载完成，触发下一次加载
	//void onMsgRouteResLoad(MsgRouteBase msg);
};

MY_END_NAMESPACE

#endif