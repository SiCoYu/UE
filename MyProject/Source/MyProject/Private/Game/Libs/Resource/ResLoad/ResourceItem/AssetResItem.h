#ifndef __AssetResItem_H
#define __AssetResItem_H

#include "ResItem.h"

/**
 * @brief uasset 类型的资源
 */
class AssetResItem : public ResItem
{
protected:

public:
	virtual void init(LoadItem* item) override;
	virtual void unload() override;

	void setPrefabName(std::string prefabName);
};

#endif