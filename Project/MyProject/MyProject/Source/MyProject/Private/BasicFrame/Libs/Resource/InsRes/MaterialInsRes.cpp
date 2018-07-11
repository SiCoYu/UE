#include "MyProject.h"
#include "MaterialInsRes.h"
#include "ResItem.h"
#include "Materials/MaterialInstanceDynamic.h"	// UMaterialInstanceDynamic
#include "Materials/MaterialInterface.h"	// UMaterialInterface
#include "Materials/MaterialInstance.h"	// UMaterialInstance, class UMaterialInstance : public UMaterialInterface
#include "Materials/Material.h"	// UMaterial, class UMaterial : public UMaterialInterface
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(MaterialInsRes, ResInsBase)

MaterialInsRes::MaterialInsRes()
{

}

UMaterialInterface* MaterialInsRes::getMaterialInterface()
{
	return this->mMaterial;
}

UMaterialInstanceDynamic* MaterialInsRes::getMaterialInterfaceDynamic()
{
	return this->mMaterialDyn;
}

void MaterialInsRes::_initWithResImpl(ResItem* res)
{
	// 获取资源单独保存
	this->mMaterial = Cast<UMaterialInterface>(res->getObject(res->getPrefabName()));
	this->mMaterialDyn = UMaterialInstanceDynamic::Create(this->mMaterial, nullptr);

	Super::_initWithResImpl(res);
}

void MaterialInsRes::unload()
{
	if (this->mMaterial != nullptr)
	{
		// 这个接口不知道行不行
		//UtilSysLibWrap::UnloadAsset(this->mMaterial);
		this->mMaterial = nullptr;

		// 这个接口肯定可以
		//UtilSysLibWrap::UnloadUnusedAssets();
	}

	Super::unload();
}

MY_END_NAMESPACE