#ifndef __ClassAssetResItem_H
#define __ClassAssetResItem_H

#include "ResItem.h"
#include "BaseClassDef.h"

/**
 * @brief uasset 类型的资源
 */
class ClassAssetResItem : public ResItem
{
	M_DECLARE_SUPER_KW(ResItem)

protected:
	UClass* mResObject;		// uasset 类型的资源

public:
	ClassAssetResItem();
	virtual ~ClassAssetResItem();

public:
	void setPrefabName(std::string prefabName);

	virtual void init(LoadItem* item) override;
	virtual UObject* getObject(std::string resName) override;
	virtual void unload() override;
};

#endif