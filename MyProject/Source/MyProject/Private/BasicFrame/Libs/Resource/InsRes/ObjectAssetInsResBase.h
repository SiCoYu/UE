﻿#ifndef __ObjectAssetInsResBase_H
#define __ObjectAssetInsResBase_H

#include "InsResBase.h"
#include <string>
#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"	// FQuat
#include "BaseClassDef.h"
#include "ResPackType.h"

class UObject;
class UClass;
class ResInsEventDispatch;

class ObjectAssetInsResBase : public InsResBase
{
	M_DECLARE_SUPER_KW(InsResBase)

protected:
	UObject* mGo;
	UObject* mRetGO;
	ResPackType mResPackType;    // 资源打包类型

public:
	ObjectAssetInsResBase();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName, bool isSetInitOrientPos = false, FVector position = FVector::ZeroVector, FQuat rotation = FQuat::Identity, ResInsEventDispatch* evtHandle = nullptr);
	UObject* getObject();
	UClass* getClass();
	virtual void unload() override;
};

#endif