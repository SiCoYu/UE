#pragma once

#include "Containers/UnrealString.h"	// FString

class MYPROJECTEDITOR_API PackageOperation
{
protected:
	FString PackageName;
	FString TextureName;
	int TextureWidth;
	int TextureHeight;

public:
	PackageOperation();
	/**
	 * @ref https://zhuanlan.zhihu.com/p/66890786
	 * @ref https://isaratech.com/
	 * @ref https://isaratech.com/ue4-programmatically-create-a-new-material-and-inner-nodes/
     * @ref https://isaratech.com/save-a-procedurally-generated-texture-as-a-new-asset/
	 */
	void saveOneTexture();
};