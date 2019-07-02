#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "UObject/NoExportTypes.h"

// error C2079: 'FMyFbxMatInfo' uses undefined struct 'FBXASSETS_API'
struct MYPROJECTEDITOR_API FMyFbxMatInfo
{
	FString Texture_DiffuseMap;
	FString Texture_SpecularMap;
	FString Texture_NormalMap;
	FString Texture_SelfIlluminationMap;
	FString Texture_OpacityMap;
	FString Texture_ReflectMap;
	FString Texture_GlossMap;
	FString Texture_SSSMask;

	FVector Vector_Diffuse;
	FVector Vector_Ambient;
	FVector Vector_Specular;

	float Scalar_SpecularLevel;
	float Scalar_Glossiness;
	float Scalar_SelfIllusionScale;

	bool bMaterialType_TwoSided;
	bool bMaterialType_HumanBody;
	bool bMaterialType_HumanFace;
	bool bOpacityMaskChannel_Alpha;
	bool bOpacityBlendModel_Translucent;

	bool bAnimatedTexture_AllTextures;
	bool bAnimatedTexture_Diffuse;
	bool bAnimatedTexture_Specular;
	bool bAnimatedTexture_Normal;
	bool bAnimatedTexture_Glow;
	bool bAnimatedTexture_Opacity;

	FMyFbxMatInfo();
};