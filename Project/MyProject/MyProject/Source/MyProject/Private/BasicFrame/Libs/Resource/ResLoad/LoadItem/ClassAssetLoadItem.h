#ifndef __ClassAssetLoadItem_H
#define __ClassAssetLoadItem_H

#include "LoadItem.h"
#include "CoreUObject.h"	// UClass \ UObject
#include "BaseClassDef.h"

/**
 * @brief 从 uasset 扩展名的本地 Package 中加载资源 Class Blueprint 类型
 */
class ClassAssetLoadItem : public LoadItem
{
	M_DECLARE_SUPER_KW(LoadItem)

protected:
	UClass* mResObj;		// uasset 类型的资源
	FStringAssetReference mAssetRef;	// 异步加载需要的

public:
	ClassAssetLoadItem();
	virtual ~ClassAssetLoadItem();

protected:
	void syncLoad();
	void asyncLoad();

public:
	void onAsyncLoaded();
	virtual UObject* getObject() override;
	virtual void setObject(UObject* value) override;

	virtual void load() override;
    // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
	virtual void unload() override;
};

#endif