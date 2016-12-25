#ifndef __ClassAssetResItem_H
#define __ClassAssetResItem_H

#include "ResItem.h"

/**
 * @brief uasset 类型的资源
 */
class ClassAssetResItem : public ResItem
{
protected:

public:
	ClassAssetResItem();

public:
	virtual void init(LoadItem* item) override;
	virtual void unload() override;

	void setPrefabName(std::string prefabName);
};

#endif