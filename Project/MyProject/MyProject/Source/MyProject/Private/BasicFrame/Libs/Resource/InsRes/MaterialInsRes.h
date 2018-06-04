#pragma once

//#include "UObject/UObjectGlobals.h"	// TSubobjectPtr
//#include "MaterialShared.h"	// FMaterial
#include "BaseClassDef.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

// class FMaterial;
class UMaterialInterface;
class UMaterial;
class UMaterialInstance;
class UMaterialInstanceDynamic;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief UE4:C++中使用材质
 * @url http://blog.csdn.net/lzt20007/article/details/51285926
 */
class MaterialInsRes : public ResInsBase
{
	M_DECLARE_CLASS(MaterialInsRes, ResInsBase);

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
	UMaterialInterface* getMaterialInterface();
	UMaterialInstanceDynamic* getMaterialInterfaceDynamic();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	virtual void unload() override;
};

MY_END_NAMESPACE