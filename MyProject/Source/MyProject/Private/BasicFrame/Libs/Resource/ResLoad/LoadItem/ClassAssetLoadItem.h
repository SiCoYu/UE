#ifndef __ClassAssetLoadItem_H
#define __ClassAssetLoadItem_H

#include "LoadItem.h"
#include "CoreUObject.h"	// Class 

/**
 * @brief 从 uasset 扩展名的本地 Package 中加载资源 Class Blueprint 类型
 */
class ClassAssetLoadItem : public LoadItem
{
protected:
	UClass* mResObj = nullptr;		// uasset 类型的资源

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
	ClassAssetLoadItem();

public:
	UClass* getResObj();
	void setResObj(UClass* value);
	virtual void load() override;
    // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
	virtual void unload() override;
};

#endif