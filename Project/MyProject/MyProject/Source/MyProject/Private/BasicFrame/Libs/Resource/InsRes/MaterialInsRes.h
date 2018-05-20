#pragma once

//#include "UObject/UObjectGlobals.h"	// TSubobjectPtr
//#include "MaterialShared.h"	// FMaterial
#include "BaseClassDef.h"
#include "InsResBase.h"

/**
* @brief
UE4:C++中使用材质
http://blog.csdn.net/lzt20007/article/details/51285926
*/

// class FMaterial;
class UMaterialInterface;
class UMaterial;
class UMaterialInstance;
class UMaterialInstanceDynamic;

class MaterialInsRes : public InsResBase
{
	M_DECLARE_SUPER_KW(InsResBase);

protected:
	//FMaterial* mMaterial;
	// Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectGlobals.h
	// #define TSubobjectPtr \
	//	EMIT_DEPRECATED_WARNING_MESSAGE("TSubobjectPtr is deprecated and should no longer be used. Please use pointers instead.") \
	// TSubobjectPtrDeprecated
	//TSubobjectPtr<FMaterial> mMaterial;
	UMaterialInterface* mMaterial;	// UMaterial \ UMaterialInstance
	UMaterialInstanceDynamic* mMaterialDyn;

public:
	MaterialInsRes();

public:
	UMaterialInterface* getMaterial();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	virtual void unload() override;
};