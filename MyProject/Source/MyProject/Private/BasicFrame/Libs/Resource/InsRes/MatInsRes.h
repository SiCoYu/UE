#pragma once

//#include "UObject/UObjectGlobals.h"	// TSubobjectPtr
//#include "MaterialShared.h"	// FMaterial
#include "InsResBase.h"

/**
* @brief
UE4:C++中使用材质
http://blog.csdn.net/lzt20007/article/details/51285926
*/

// class FMaterial;
class UMaterial;
class UMaterialInstanceDynamic;

class MatInsRes : InsResBase
{
	typedef InsResBase Super;

protected:
	//FMaterial* mMat;
	// Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectGlobals.h
	// #define TSubobjectPtr \
	//	EMIT_DEPRECATED_WARNING_MESSAGE("TSubobjectPtr is deprecated and should no longer be used. Please use pointers instead.") \
	// TSubobjectPtrDeprecated
	//TSubobjectPtr<FMaterial> mMat;
	UMaterialInstance* mMatIns;
	UMaterialInstanceDynamic* mMatDyn;

public:
	MatInsRes();

public:
	UMaterial* getMat();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	virtual void unload() override;
};