#ifndef __ObjectAssetLoadItem_H
#define __ObjectAssetLoadItem_H

#include "LoadItem.h"
#include "CoreUObject.h"	// UObject 
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 从 uasset 扩展名的本地 Package 中加载资源
 */
class ObjectAssetLoadItem : public LoadItem
{
	M_DECLARE_CLASS(ObjectAssetLoadItem, LoadItem)

protected:
	UObject* mResObject;		// uasset 类型的资源
	FStringAssetReference mAssetRef;	// 异步加载需要的

protected:
	void syncLoad();
	void asyncLoad();

public:
	ObjectAssetLoadItem();
	virtual ~ObjectAssetLoadItem();

public:
	void onAsyncLoaded();
	UObject* getObject();
	void setObject(UObject* value);
	virtual void load() override;
    // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
	virtual void unload() override;
};

MY_END_NAMESPACE

#endif