#include "MyProject.h"
#include "MatRes.h"
#include "Materials/MaterialInstanceDynamic.h"	// UMaterialInstanceDynamic
#include "Materials/Material.h"	// UMaterial, class UMaterial : public UMaterialInterface

MatRes::MatRes()
{

}

FMaterial* MatRes::getMat()
{
    return this->mMat;
}

void MatRes::initImpl(ResItem* res)
{
    // 获取资源单独保存
	this->mMat = Cast<FMaterial>(res->getObject(res->getPrefabName()));
	this->mMatDyn = UMaterialInstanceDynamic::Create(this->mMatIns, nullptr);

    base.initImpl(res);
}

void MatRes::unload()
{
    if (this->mMat != nullptr)
    {
        // 这个接口不知道行不行
        //UtilApi::UnloadAsset(m_mat);
		this->mMat = nullptr;

        // 这个接口肯定可以
        //UtilApi.UnloadUnusedAssets();
    }

	Super::unload();
}