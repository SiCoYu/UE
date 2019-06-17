#ifndef __ClassAssetResItem_H
#define __ClassAssetResItem_H

#include "ResItem.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

class UClass;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief uasset 类型的资源
 */
class ClassAssetResItem : public ResItem
{
	M_DECLARE_CLASS(ClassAssetResItem, ResItem)

protected:
	UClass* mResObject;		// uasset 类型的资源

public:
	ClassAssetResItem();
	virtual ~ClassAssetResItem();

public:
	void setPrefabName(std::string prefabName);
	virtual UObject* getObject(std::string resName) override;
	virtual void initWithLoad(LoadItem* item) override;
	virtual void unload() override;
};

MY_END_NAMESPACE

#endif