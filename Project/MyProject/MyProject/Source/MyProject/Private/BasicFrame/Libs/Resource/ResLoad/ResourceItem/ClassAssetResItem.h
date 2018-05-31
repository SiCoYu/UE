﻿#ifndef __ClassAssetResItem_H
#define __ClassAssetResItem_H

#include "ResItem.h"
#include "BaseClassDef.h"
#include "PlatformDefine.h"

class UClass;

MY_BEGIN_NAMESPACE(MyNS)

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
	virtual UObject* getObject(std::string resName) override;
	virtual void init(LoadItem* item) override;
	virtual void unload() override;
};

MY_END_NAMESPACE

#endif