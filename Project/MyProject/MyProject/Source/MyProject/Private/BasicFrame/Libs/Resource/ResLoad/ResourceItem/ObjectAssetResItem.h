#ifndef __ObjectAssetResItem_H
#define __ObjectAssetResItem_H

#include "ResItem.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

class UObject;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief uasset 类型的资源
 */
class ObjectAssetResItem : public ResItem
{
	M_DECLARE_CLASS(ObjectAssetResItem, ResItem)

protected:
	UObject* mResObject;		// uasset 类型的资源

public:
	ObjectAssetResItem();
	virtual ~ObjectAssetResItem();

public:
	void setPrefabName(std::string prefabName);
	virtual UObject* getObject(std::string resName) override;
	virtual void initWithLoad(LoadItem* item) override;
	virtual void unload() override;
};

MY_END_NAMESPACE

#endif