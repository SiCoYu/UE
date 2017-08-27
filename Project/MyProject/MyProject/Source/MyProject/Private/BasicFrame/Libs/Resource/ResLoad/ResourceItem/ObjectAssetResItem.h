#ifndef __ObjectAssetResItem_H
#define __ObjectAssetResItem_H

#include "ResItem.h"
#include "BaseClassDef.h"

/**
 * @brief uasset 类型的资源
 */
class ObjectAssetResItem : public ResItem
{
	M_DECLARE_SUPER_KW(ResItem)

public:
	ObjectAssetResItem();
	virtual ~ObjectAssetResItem();

public:
	virtual void init(LoadItem* item) override;
	virtual void unload() override;

	void setPrefabName(std::string prefabName);
};

#endif