#ifndef __ObjectAssetResItem_H
#define __ObjectAssetResItem_H

#include "ResItem.h"
#include "BaseClassDef.h"

class UObject;

/**
 * @brief uasset 类型的资源
 */
class ObjectAssetResItem : public ResItem
{
	M_DECLARE_SUPER_KW(ResItem)

protected:
	UObject* mResObject;		// uasset 类型的资源

public:
	ObjectAssetResItem();
	virtual ~ObjectAssetResItem();

public:
	void setPrefabName(std::string prefabName);
	virtual UObject* getObject(std::string resName) override;
	virtual void init(LoadItem* item) override;
	virtual void unload() override;
};

#endif