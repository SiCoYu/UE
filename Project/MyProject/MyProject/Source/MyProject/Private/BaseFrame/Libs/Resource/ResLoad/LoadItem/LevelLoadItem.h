#ifndef __LevelLoadItem_H
#define __LevelLoadItem_H

#include "LoadItem.h"
#include <string>
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "MyDelegateDef.h"
#include "IDispatchObject.h"
#include "Delegates/IDelegateInstance.h"	// FDelegateHandle
#include "PlatformDefine.h"

class UMyDelegateLevelLoad;

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 从本地磁盘加载 umap 扩展类型的资源
*/
class LevelLoadItem : public LoadItem
{
	M_DECLARE_CLASS(LevelLoadItem, LoadItem)

protected:
	std::string mLevelName;
	UMyDelegateLevelLoad* mMyDelegateLevelLoad;

	//FMyDelegateDef::MyDelegateBaseHandle mOnLevelLoadDelegate;
	//FDelegateHandle mOnLevelLoadDelegateHandle;

public:
	LevelLoadItem();
	virtual ~LevelLoadItem();

public:
	void setLevelName(std::string levelName);
	std::string getLevelName();

	virtual void load() override;
	virtual void unload() override;
	virtual void reset() override;

protected:
	void loadFromAssetBundleByCoroutine();
	void loadFromAssetBundle();
	void assetAssetBundlesLevelLoaded(IDispatchObject* dispObj);
};

MY_END_NAMESPACE

#endif