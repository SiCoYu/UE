#ifndef __ObjectAssetLoadItem_H
#define __ObjectAssetLoadItem_H

#include "LoadItem.h"
#include "CoreUObject.h"	// UObject 
#include "BaseClassDef.h"	// M_DECLARE_SUPER_KW

/**
 * @brief 从 uasset 扩展名的本地 Package 中加载资源
 */
class ObjectAssetLoadItem : public LoadItem
{
	M_DECLARE_SUPER_KW(LoadItem)

protected:
	UObject* mResObject;		// uasset 类型的资源

protected:
	//void loadFromDefaultAssetBundle()
	//{
	//	m_prefabObj = Resources.Load<Object>(mPathNoExt);

	//	if (m_prefabObj != null)
	//	{
	//		nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
	//	}
	//	else
	//	{
	//		nonRefCountResLoadResultNotify.resLoadState.setFailed();
	//	}
	//	nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
	//}

	//IEnumerator loadFromDefaultAssetBundleByCoroutine()
	//{
	//	ResourceRequest req = Resources.LoadAsync<Object>(mPathNoExt);
	//	yield return req;

	//	if (req.asset != null && req.isDone)
	//	{
	//		m_prefabObj = req.asset;
	//		nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
	//	}
	//	else
	//	{
	//		nonRefCountResLoadResultNotify.resLoadState.setFailed();
	//	}

	//	nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
	//}
	void syncLoad();
	void asyncLoad();

public:
	ObjectAssetLoadItem();
	virtual ~ObjectAssetLoadItem();

public:
	UClass* getObject();
	void setObject(UObject* value);
	virtual void load() override;
    // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
	virtual void unload() override;
};

#endif