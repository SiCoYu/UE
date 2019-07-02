#include "MyFbxMatInfo.h"

FMyFbxMatInfo::FMyFbxMatInfo()
{
	Scalar_SpecularLevel = -1.f;
	Scalar_Glossiness = -1.f;
	Scalar_SelfIllusionScale = -1.f;

	Vector_Diffuse = FVector(1.f, 1.f, 1.f);
	Vector_Specular = FVector(1.f, 1.f, 1.f);
	Vector_Ambient = FVector(1.f, 1.f, 1.f);


	bMaterialType_TwoSided = false;
	bMaterialType_HumanBody = false;
	bMaterialType_HumanFace = false;
	bOpacityMaskChannel_Alpha = true;
	bOpacityBlendModel_Translucent = false;

	bAnimatedTexture_AllTextures = false;
	bAnimatedTexture_Diffuse = false;
	bAnimatedTexture_Specular = false;
	bAnimatedTexture_Normal = false;
	bAnimatedTexture_Glow = false;
	bAnimatedTexture_Opacity = false;

}