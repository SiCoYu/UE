#include "MyProject.h"
#include "MatInsRes.h"
#include "ResItem.h"
#include "Materials/MaterialInstanceDynamic.h"	// UMaterialInstanceDynamic
#include "Materials/MaterialInterface.h"	// UMaterialInterface
#include "Materials/MaterialInstance.h"	// UMaterialInstance, class UMaterialInstance : public UMaterialInterface
#include "Materials/Material.h"	// UMaterial, class UMaterial : public UMaterialInterface

MatInsRes::MatInsRes()
{

}

UMaterialInterface* MatInsRes::getMat()
{
	return this->mMat;
}

void MatInsRes::initImpl(ResItem* res)
{
	// 获取资源单独保存
	this->mMat = Cast<UMaterialInterface>(res->getObject(res->getPrefabName()));
	this->mMatDyn = UMaterialInstanceDynamic::Create(this->mMat, nullptr);

	Super::initImpl(res);
}

void MatInsRes::unload()
{
	if (this->mMat != nullptr)
	{
		// 这个接口不知道行不行
		//UtilApi::UnloadAsset(this->mMat);
		this->mMat = nullptr;

		// 这个接口肯定可以
		//UtilApi.UnloadUnusedAssets();
	}

	Super::unload();
}