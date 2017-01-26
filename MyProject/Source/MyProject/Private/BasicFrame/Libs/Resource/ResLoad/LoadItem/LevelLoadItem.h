#ifndef __LevelLoadItem_H
#define __LevelLoadItem_H

#include "LoadItem.h"
#include <string>
#include "BaseClassDef.h"
#include "MyDelegateDef.h"
#include "IDispatchObject.h"
#include "Delegates/IDelegateInstance.h"	// FDelegateHandle

class UMyDelegateLevelLoad;

/**
* @brief 从本地磁盘加载 umap 扩展类型的资源
*/
class LevelLoadItem : public LoadItem
{
	M_DECLARE_SUPER_KW(LoadItem)

protected:
	std::string mLevelName;
	UMyDelegateLevelLoad* mMyDelegateLevelLoad;

	FMyDelegateDef::MyDelegateBaseHandle::FDelegate mOnLevelLoadDelegate;
	FDelegateHandle mOnLevelLoadDelegateHandle;

public:
	LevelLoadItem();
	~LevelLoadItem();

public:
	void setLevelName(std::string levelName);
	std::string getLevelName();

	virtual void load() override;
	virtual void unload() override;
	virtual void reset() override;

protected:
	void loadFromAssetBundleByCoroutine();
	void loadFromAssetBundle();
	void assetAssetBundlesLevelLoaded();
};

#endif